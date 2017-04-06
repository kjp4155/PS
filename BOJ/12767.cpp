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
#include <bitset>
#include <sstream> 
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
int N,M,K,T,tc;

int cur; int val[100][100]; int l[100][100],r[100][100];

int pa[100];
int FIND(int x){
	if( pa[x] == x )return x;
	return pa[x] = FIND(pa[x]);
}
void uni(int a, int b){
	a = FIND(a); b = FIND(b);
	pa[a] = b;
}
int n;
void adfs(int x, int value){
	if( value < val[n][x] && l[n][x] == 0 ){
		l[n][x] = cur; return;
	}
	if( value > val[n][x] && r[n][x] == 0 ){
		r[n][x] = cur; return;
	}
	if( value < val[n][x] && l[n][x] != 0 ){
		adfs(l[n][x],value);
		return;
	}
	if( value > val[n][x] && r[x] != 0 ){
		adfs(r[n][x],value);
	}
}

bool idk(int a, int b, int ra, int rb){
	if( l[a][ra] == 0 && l[b][rb] != 0 ) return false;
	if( r[a][ra] == 0 && r[b][rb] != 0 ) return false;
	if( l[a][ra] != 0 && l[b][rb] == 0 ) return false;
	if( r[a][ra] != 0 && r[b][rb] == 0 ) return false;

	if( l[a][ra] == 0 && l[b][rb] == 0 && r[a][ra] == 0 && r[b][rb] == 0 ) return true;
	bool res = true;
	if( l[a][ra] != 0 ) res &= idk(a,b,l[a][ra],l[b][rb]);
	if( r[a][ra] != 0 ) res &= idk(a,b,r[a][ra],r[b][rb]);
	return res; 
}

int main(void){
	geti(N,K); repp(i,N) pa[i] = i;
	int root;
	for(n=1;n<=N;n++){
		int x; geti(x); root = 1; val[n][1] = x;
		for(cur=2;cur<=K;cur++){
			int x; geti(x); val[n][cur] = x; adfs(1,x);
		}
	}

	repp(i,N){
		repp(j,N){
			if( idk(i,j,1,1) )if(i<j){
	//			printf("%d %d\n",i,j);
				uni(i,j);
			}
		}
	}

	set<int> s;
	repp(i,N) s.insert(FIND(i));
	cout << s.size();

}

