
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
typedef long long int64;
const double pi=acos(-1.0);//NOTES:pi
const double eps=1e-11;//NOTES:eps
template<class T> inline T lowbit(T n){return (n^(n-1))&n;}//NOTES:lowbit(
template<class T> inline int countbit(T n){return (n==0)?0:(1+countbit(n&(n-1)));}//NOTES:countbit(
template<class T> inline T gcd(T a,T b)//NOTES:gcd(
{if(a<0)return gcd(-a,b);if(b<0)return gcd(a,-b);return (b==0)?a:gcd(b,a%b);}
template<class T> inline T lcm(T a,T b)//NOTES:lcm(
{if(a<0)return lcm(-a,b);if(b<0)return lcm(a,-b);return a*(b/gcd(a,b));}
template<class T> string toString(T n){ostringstream ost;ost<<n;ost.flush();return ost.str();}//NOTES:toString(
int toInt(string s){int r=0;istringstream sin(s);sin>>r;return r;}//NOTES:toInt(
int64 toInt64(string s){int64 r=0;istringstream sin(s);sin>>r;return r;}//NOTES:toInt64(
double toDouble(string s){double r=0;istringstream sin(s);sin>>r;return r;}//NOTES:toDouble(
vector<string> split( const string& s, const string& delim =" " ) {
  vector<string> res;
  string t;
  for (unsigned i = 0 ; i != s.size() ; i++ ) {
    if ( delim.find( s[i] ) != string::npos ) {
      if ( !t.empty() ) {
        res.push_back( t );
        t = "";
      }
    } else {
      t += s[i];
    }
  }
  if ( !t.empty() ) {
    res.push_back(t);
  }
  return res;
}

const int MAXN = 30;
int n, m;
int a[MAXN][MAXN];
int b[MAXN][MAXN];
int res;
int totalneed;


int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

int inside(int i, int j) {
  return i>=0 && i<m && j>=0 && j<n;
}


int isBad1(int i, int j, int x, int y, int k1, int k2) {
  if(inside(x, y) && b[x][y] != 0) {
    int x_1 = i+dx[k1];
    int y_1 = j+dy[k1];
    int x_2 = i+dx[k2];
    int y_2 = j+dy[k2];
    if(inside(x_1, y_1) && inside(x_2, y_2) && b[x_1][y_1] == 0 && b[x_2][y_2] == 0)
      return 1;
  }
  return 0;
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
      && !isBad1(x, y, x+dx[k], y+dy[k], (k+3)%4, (k+1)%4))
      go(x, y, cnt+1);
  }
  b[i][j] = 0;
}

int main() {
  freopen("input.txt", "r", stdin);
  scanf("%d%d", &n, &m);
  fori(i,m)fori(j,n)scanf("%d", &a[i][j]);
  res=0;
  memset(b, 0, sizeof(b));
  totalneed = m*n;
  fori(i,m)fori(j,n)if(a[i][j]==1) totalneed--,b[i][j]=2;
  printf("%d\n", totalneed);
  fori(i,m)fori(j,n)if(a[i][j]==2)
    go(i,j,1);
  printf("%d\n", res);
  fclose(stdin);
  return 0;
}
