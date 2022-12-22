#include<bits/stdc++.h>

using namespace std;

const int maxn = 18;

int n;
int m;
int dp[maxn][maxn][1 << maxn];
bool has_edge[maxn][maxn];
map < int, int > v[maxn];
int p[maxn][maxn][1 << maxn];
stack < int > st;

void input();
void find_ans();
void fill_dp();
void find_tsp(int i, int j, int mask);
void print_st();
bool is_1bit(int number, int bit);
int count_1bit(int number);

int main() {
  input();
  fill_dp();
  find_ans();
}

void input() {
  cout << "Enter number of vertices and edges: ";
  cin >> n >> m;
  cout << "Enter edge in format (from,to,value):" << endl;
  for (int i = 0; i < m; i++) {
    int from, to, val;
    cin >> from >> to >> val;
    from--;
    to--; //0 base
    has_edge[from][to] = true;
    v[from][to] = val;
  }

}

void fill_dp() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int z = 0; z < (1 << n); z++) {
        if (is_1bit(z, i) && is_1bit(z, j) && j != i && has_edge[i][j] && count_1bit(z) == 2) {
          dp[i][j][z] = v[i][j];
        } else if (is_1bit(z, i) && is_1bit(z, j) && j == i && count_1bit(z) == 1) {
          dp[i][j][z] = 0;
        } else {
          dp[i][j][z] = ((int) 1e9 + 10);
        }
      }
    }
  }
}

bool is_1bit(int number, int bit) {
  return (number & (1 << bit) != 0);
}

int count_1bit(int number) {
  int c = 0;
  int p = 0;
  while ((1 << p) <= number) {
    if ((number & (1 << p)) != 0) {
      c++;
    }
    p++;
  }
  return c;
}

void find_tsp(int i, int j, int mask) {
  if (i == j) {
    int c = count_1bit(mask);
    if (c == 1) {
      dp[i][j][mask] = 0;
      p[i][j][mask] = i;
    } else {
      for (int l = 0; l < n; l++) {
        if (((mask & (1 << l)) != 0) && has_edge[l][j]) {
          if (dp[i][l][mask] + v[l][j] <= dp[i][j][mask]) {
            dp[i][j][mask] = dp[i][l][mask] + v[l][j];
          }

        }
      }
    }
    return;
  }

  for (int l = 0; l < n; l++) {
    if (((mask & (1 << l)) != 0) && has_edge[l][j]) {
      if (dp[i][l][mask ^ (1 << j)] + v[l][j] <= dp[i][j][mask]) {
        dp[i][j][mask] = dp[i][l][mask ^ (1 << j)] + v[l][j];
      }
    }
  }

  return;
}

void find_ans() {
  for (int i = 0; i < n; i++) {
    for (int z = 0; z < (1 << n); z++) {
      for (int j = 0; j < n; j++) {
        if (is_1bit(z, i) && is_1bit(z, j)) {
          find_tsp(i, j, z);
        }
      }
    }
  }
  int ans = INT_MAX;
  int root = -1;
  for (int i = 0; i < n; i++) {
    if (ans > dp[i][i][(1 << n) - 1]) {
      ans = dp[i][i][(1 << n) - 1];
      root = i;
    }
  }
  cout << "answer : " << ans << endl;
}