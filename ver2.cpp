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

#define fori(i,n) for(int i=0; i<(n); i++)
#define fori1(i,n) for(int i=1; i<=(n); i++)
#define rep(i, a, b) for(int i=(a);i<=(b);i++)
#define forv(i, a) for(unsigned i=0; i<a.size(); i++)
const int MAXN = 103;
int n, m;
int a[MAXN][MAXN];
int b[MAXN][MAXN];
int ske[MAXN][MAXN];
int res;
int totalneed;
int boundaryCnt;


int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

int isBad1(int i, int j, int x, int y, int k1, int k2) {
  if(b[x][y] == 1) {
    int x_1 = i+dx[k1];
    int y_1 = j+dy[k1];
    int x_2 = i+dx[k2];
    int y_2 = j+dy[k2];
    if(b[x_1][y_1] == 0 && b[x_2][y_2] == 0)
      return 1;
  }
  return 0;
}

int isBad(int i, int j, int x, int y) {
  if(boundaryCnt == 0)
    return 0;

  if(x==1 && i==2 && y>1 && y<n) {
    if(b[1][y-1] == 0 && b[1][y+1] == 0) return 1;
  }
  if(x==m && i==m-1 && y>1 && y<n) {
    if(b[x][y-1] == 0 && b[x][y+1] == 0) return 1;
  }

  if(y==1 && j==2 && x>1 && x<m) {
    if(b[x-1][y] == 0 && b[x+1][y]==0) return 1;
  }

  if(y==n && j==n-1 && x>1 && x<m) {
    if(b[x-1][y] == 0 && b[x+1][y]==0) return 1;
  }

  return 0;
}


int isOk(int i, int j, int k) {
  fori(v, 4) if (v!=k) {
    int x = i+dx[v];
    int y = j+dy[v];

    if(b[x][y] == 0) {
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

    if(b[x][y] == 0) {
      ske[x][y]--;
    }
  }
}

void restoreSke(int i, int j, int k) {
  fori(v, 4) if (v!=k) {
    int x = i+dx[v];
    int y = j+dy[v];

    if(b[x][y] == 0) {
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
  if(i == 1 || j == 1 || i == m || j == n)
    boundaryCnt++;

  fori(k, 4) {
    int x = i+dx[k];
    int y = j+dy[k];
    if(b[x][y] == 0 && (a[x][y] == 0 || (a[x][y] == 3 && cnt == totalneed-1)) && !isBad(i, j, x, y)
      && !isBad1(x, y, x+dx[k], y+dy[k], (k+3)%4, (k+1)%4) && isOk(i, j, k)) {
      changeSke(i, j, k);
      go(x, y, cnt+1);
      restoreSke(i, j, k);
    }
  }

  if(i == 1 || j == 1 || i == m || j == n)
    boundaryCnt--;
  b[i][j] = 0;
}

int main() {
  //freopen("test.in", "r", stdin);
  scanf("%d%d", &n, &m);
  fori(i,m+2)fori(j,n+2) b[i][j]=2;
  fori(i,m)fori(j,n)scanf("%d", &a[i+1][j+1]);

  res=0;
  boundaryCnt = 0;
  totalneed = m*n;
  memset(ske, 0, sizeof(ske));
  fori1(i,m)fori1(j,n)
    if(a[i][j]==1) totalneed--,b[i][j]=2;
    else b[i][j] = 0;

  fori1(i,m)fori1(j,n)if(a[i][j]!=1) fori(k,4){
    int x=i+dx[k];
    int y=j+dy[k];
    if(b[x][y]!=2) ske[i][j]++;
  }

  fori1(i,m)fori1(j,n)if(a[i][j] == 0 && ske[i][j] < 2) {
    printf("0\n");
    return 0;
  }

  fori1(i,m)fori1(j,n)if(a[i][j]==2)
    go(i,j,1);

  printf("%d\n", res);
  fclose(stdin);
  return 0;
}
