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
const int MAXN = 103;
int n, m;
int a[MAXN][MAXN];
int b[MAXN][MAXN];
int ske[MAXN][MAXN];
int res;
int totalneed;


int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

int inside(int i, int j) {
  return i>=0 && i<m && j>=0 && j<n;
}


int isBad1(int i, int j, int x, int y, int k1, int k2) {
  return 0;
  /*
  if(inside(x, y) && b[x][y] != 0) {
    int x_1 = i+dx[k1];
    int y_1 = j+dy[k1];
    int x_2 = i+dx[k2];
    int y_2 = j+dy[k2];
    if(inside(x_1, y_1) && inside(x_2, y_2) && b[x_1][y_1] == 0 && b[x_2][y_2] == 0)
      return 1;
  }
  return 0;
  */
}

int isBad(int i, int j, int x, int y) {
  if(x==0 && i==1 && y>0 && y<n-1) {
    if(b[0][y-1] == 0 && b[0][y+1] == 0) return 1;
  }
  if(x==m-1 && i==m-2 && y>0 && y<n-1) {
    if(b[x][y-1] == 0 && b[x][y+1] == 0) return 1;
  }

  if(y==0 && j==1 && x>0 && x<m-1) {
    if(b[x-1][y] == 0 && b[x+1][y]==0) return 1;
  }

  if(y==n-1 && j==n-2 && x>0 && x<m-1) {
    if(b[x-1][y] == 0 && b[x+1][y]==0) return 1;
  }

  return 0;
}


int isOk(int i, int j, int k) {
  fori(v, 4) if (v!=k) {
    int x = i+dx[v];
    int y = j+dy[v];

    if(inside(x, y) && b[x][y] == 0) {
      if(a[x][y] == 3 && ske[x][y] <= 1) return 0;
      if(a[x][y] == 0 && ske[x][y] <= 2) return 0;
    }
  }
  return 1;
}

void changeSke(int i, int j, int k) {
  fori(v, 4) if (v!=k) {
    int x = i+dx[v];
    int y = j+dy[v];

    if(inside(x, y) && b[x][y] == 0 && a[x][y] != 1) {
      ske[x][y]--;
    }
  }
}

void restoreSke(int i, int j, int k) {
  fori(v, 4) if (v!=k) {
    int x = i+dx[v];
    int y = j+dy[v];

    if(inside(x, y) && b[x][y] == 0 && a[x][y] != 1) {
      ske[x][y]++;
    }
  }
}

void go(int i, int j, int cnt) {
  if(cnt == totalneed) {
    if(a[i][j] == 3)
      res++;
    return;
  }
  b[i][j] = 1;
  fori(k, 4) {
    int x = i+dx[k];
    int y = j+dy[k];
    if(inside(x, y) && b[x][y] == 0 && (a[x][y] == 0 || (a[x][y] == 3 && cnt == totalneed-1)) && !isBad(i, j, x, y)
      && !isBad1(x, y, x+dx[k], y+dy[k], (k+3)%4, (k+1)%4) && isOk(i, j, k)) {
      changeSke(i, j, k);
      go(x, y, cnt+1);
      restoreSke(i, j, k);
    }
  }
  b[i][j] = 0;
}

int main() {
  //freopen("test.in3", "r", stdin);
  scanf("%d%d", &n, &m);
  fori(i,m)fori(j,n)scanf("%d", &a[i][j]);

  res=0;
  totalneed = m*n;
  memset(b, 0, sizeof(b));
  memset(ske, 0, sizeof(ske));
  fori(i,m)fori(j,n)if(a[i][j]==1) totalneed--,b[i][j]=2;
  fori(i,m)fori(j,n)if(a[i][j]!=1) fori(k,4){
    int x=i+dx[k];
    int y=j+dy[k];
    if(inside(x, y) && a[x][y]!=1) ske[i][j]++;
  }
  fori(i,m)fori(j,n)if(a[i][j] == 0 && ske[i][j] < 2) {
    printf("0\n");
    return 0;
  }

  fori(i,m)fori(j,n)if(a[i][j]==2)
    go(i,j,1);
  printf("%d\n", res);
  fclose(stdin);
  return 0;
}
