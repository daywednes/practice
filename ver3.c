#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define fori(i,n) for(int i=0; i<(n); i++)
#define fori1(i,n) for(int i=1; i<=(n); i++)
#define MAXN 103

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
  int v, x, y;
  for(v=0; v < 4; v++) if (v != k) {
    x = i+dx[v];
    y = j+dy[v];

    if(b[x][y] == 0) {
      if(a[x][y] == 3 && ske[x][y] <= 1) return 0;
      if(a[x][y] == 0 && ske[x][y] <= 2) return 0;
    }
  }
  return 1;
}

void changeSke(int i, int j, int k) {
  int v, x, y;
  for(v = 0; v < 4; v++) if (v != k) {
    x = i+dx[v];
    y = j+dy[v];

    if(b[x][y] == 0) {
      ske[x][y]--;
    }
  }
}

void restoreSke(int i, int j, int k) {
  int v, x, y;
  for(v = 0; v < 4; v++) if (v != k) {
    x = i+dx[v];
    y = j+dy[v];

    if(b[x][y] == 0) {
      ske[x][y]++;
    }
  }
}

void go(int i, int j, int cnt) {
  int k, x, y;
  if(cnt == totalneed) {
    if(a[i][j] == 3)
      res++;
    return;
  }
  b[i][j] = 1;
  if(i == 1 || j == 1 || i == m || j == n)
    boundaryCnt++;
  for(k = 0; k < 4; k++) {
    x = i+dx[k];
    y = j+dy[k];
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
  int x, y, i, j, k;
  //freopen("test.in", "r", stdin);
  scanf("%d%d", &n, &m);

  for(i = 0; i < m+2; i++) for(j = 0; j < n+2; j++) b[i][j] = 2;
  for(i = 0; i < m; i++) for(j = 0; j < n; j++) scanf("%d", &a[i+1][j+1]);

  res=0;
  boundaryCnt = 0;
  totalneed = m*n;
  memset(ske, 0, sizeof(ske));
  for(i = 1; i <= m; i++) for(j = 1; j<=n; j++)
    if(a[i][j]==1) totalneed--,b[i][j]=2;
    else b[i][j] = 0;

  for(i = 1; i <= m; i++) for(j = 1; j <=n; j++) if(a[i][j] != 1) for(k = 0; k < 4; k++) {
    x=i+dx[k];
    y=j+dy[k];
    if(b[x][y]!=2) ske[i][j]++;
  }

  for(i = 1; i <= m; i++) for(j = 1; j <= n; j++) if(a[i][j] == 0 && ske[i][j] < 2) {
    printf("0\n");
    return 0;
  }

  for(i = 1; i <= m; i++) for(j = 1; j <= n; j++) if(a[i][j] == 2)
    go(i,j,1);

  printf("%d\n", res);
  fclose(stdin);
  return 0;
}
