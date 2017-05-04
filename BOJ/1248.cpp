#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <memory.h>
#include <math.h>
#include <assert.h>
#include <queue>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <stack>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> Pi;
typedef pair<ll,ll> Pll;

#define Fi first
#define Se second
#define pb(x) push_back(x)
#define sz(x) (int)x.size()
#define rep(i, n) for(int i=0;i<n;i++)
#define repp(i, n) for(int i=1;i<=n;i++)
#define all(x) x.begin(), x.end()

#define ABS(x) (((x) > 0 ) ? (x) : (-(x)))
#define MAX2(x, y) (((x) > (y)) ? (x) : (y))
#define MIN2(x, y) (((x) < (y)) ? (x) : (y))

#define MAX3(x, y, z) ( (x) > (y)  ? ( (x) > (z) ? (x) : (z)  ) : ( (y) > (z) ? (y) : (z) )  )
#define MIN3(x, y, z) ( (x) < (y)  ? ( (x) < (z) ? (x) : (z)  ) : ( (y) < (z) ? (y) : (z) )  )
#define MID3(val1,val2,val3) MAX2(MIN2(MAX2(val1,val2),val3),MIN2(val1,val2))

#define geti1(X) scanf("%d",&X)
#define geti2(X,Y) scanf("%d%d",&X,&Y)
#define geti3(X,Y,Z) scanf("%d%d%d",&X,&Y,&Z)
#define geti4(X,Y,Z,W) scanf("%d%d%d%d",&X,&Y,&Z,&W)

#define GET_MACRO(_1,_2,_3,_4,NAME,...) NAME
#define geti(...) GET_MACRO(__VA_ARGS__, geti4, geti3, geti2, geti1) (__VA_ARGS__)

#define INF 987654321
#define IINF 987654321987654321

int N,M,T,K,H;
int p[100][100];
char q[100][100];
int type[100];
int arr[100];
bool done = false;
// n번째 자리 x로 채움
void solve(int n, int x){
	if( n == N+1 ){
		done = true;
		repp(i,N) printf("%d ", arr[i]);
	}
	arr[n] = x*type[n];
	for(int i=1;i<=n;i++){
		int sum = 0;
		for(int j=i;j<=n;j++){
			sum += arr[j];
			if( sum > 0 && q[i][j] != '+' ) return;
			if( sum == 0 && q[i][j] != '0' ) return;
			if( sum < 0 && q[i][j] != '-' ) return;
		}
	}

	if( type[n+1] != 0 ){
		for(int i=1;i<=10;i++) if( !done ) solve(n+1,i);
	}
	else{
		if( !done ) solve(n+1,0);
	}
}

int main(){
	scanf("%d\n",&N);
	for(int i=1;i<=N;i++){
		for(int j=i;j<=N;j++) scanf("%c",&q[i][j]);
	}
	for(int i=1;i<=N;i++){
		if( q[i][i] == '+' ) type[i] = 1;
		if( q[i][i] == '0' ) type[i] = 0;
		if( q[i][i] == '-' ) type[i] = -1;
	}
	
	solve(0,0);
}
