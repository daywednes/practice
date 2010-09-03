#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

#define fori(i,n) for(int i=0; i<n; i++)
#define rep(i, a, b) for(int i=a;i<=b;i++)
#define forv(i, a) for(unsigned i=0; i<a.size(); i++)

#define MAXN 10
int a[MAXN][MAXN], passed[MAXN][MAXN], ske[MAXN][MAXN];
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};
int res = 0;
int ncell;
int n, m;

void read_input() {
  scanf("%d%d", &n, &m);
  rep(i, 0, m+1) rep(j, 0, n+1) a[i][j] = 1;
  rep(i, 1, m) rep(j, 1, n)
    scanf("%d", &a[i][j]);
}

void init() {
  memset(ske, 0, sizeof(ske));
  memset(passed, 0, sizeof(passed));
  rep(i, 1, m) rep(j, 1, n) if (a[i][j] != 1) fori(k, 4) {
    int x = i+dx[k];
    int y = j+dy[k];
    ske[i][j] += a[x][y] != 1;
  }

  ncell = 0;
  rep(i, 1, m) rep(j, 1, n) ncell += a[i][j] != 1;

  /*
  fprintf(stderr, "%d\n", ncell);
  rep(i, 1, m) {
    rep(j, 1, n) printf("%4d", a[i][j]);
    printf("\n");
  }
  printf("***************\n");
  rep(i, 1, m) {
    rep(j, 1, n) printf("%4d", ske[i][j]);
    printf("\n");
  }
  */

  res = 0;
}

void go(int i, int j, int cnt) {
  if(cnt == ncell - 1) {
    if(a[i][j] == 3) res++;
    return;
  }

  if(a[i][j] == 3) return;
  passed[i][j] = 1;

  fori(k, 4) {
    int x = i+dx[k];
    int y = j+dy[k];
    if(a[x][y] != 1 && passed[x][y] == 0) {
      go(x, y, cnt+1);
    }
  }
  passed[i][j] = 0;
}

int main() {
  //freopen("test.in", "r", stdin);

  read_input();
  init();

  rep(i, 1, m) rep(j, 1, n) if(a[i][j] == 2)
    go(i, j, 0);

  printf("%d\n", res);
  return 0;
}
