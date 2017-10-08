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
#include <sstream>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> Pi;
typedef pair<ll, ll> Pll;
#define Fi first
#define Se second
#define pb(x) push_back(x)
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

int N,K,M,tc,T;

// Centroid Decomposition With LCA
// SPOJ QTREE5 , https://www.acmicpc.net/problem/13514

#define MAXV 100500
#define LOGV 18
vector<int> E[MAXV]; int pa[LOGV][MAXV]; int centpa[MAXV];
bool die[MAXV]; int sz[MAXV]; int level[MAXV]; int color[MAXV];
multiset<int> ans[MAXV];

int dfs_sz(int x, int p){
	sz[x] = 1;
	for(auto e : E[x])if(e!=p&&!die[e]){
		sz[x] += dfs_sz(e,x);
	}
	return sz[x];
}

void dfs_build(int x, int p, int lev){
	level[x] = lev; pa[0][x] = p;
	for(auto e : E[x])if(e!=p&&!die[e]){
		dfs_build(e,x,lev+1);
	}
}

void build_lca(){
	for(int k=1;k<LOGV;k++){
		repp(i,N){
			if( pa[k-1][i] != -1 ) pa[k][i] = pa[k-1][pa[k-1][i]];
			else pa[k][i] = -1;
		}
	}
}

int lca(int x, int y){
	if( level[x] > level[y] ) swap(x,y);
	int diff = level[y] - level[x];
	for(int k=LOGV-1;k>=0;k--){
		if( diff & (1<<k) ) y = pa[k][y];
	}
	if( x == y ) return x;
	for(int k=LOGV-1;k>=0;k--){
		if( pa[k][x] != pa[k][y] ){
			x = pa[k][x]; y = pa[k][y];
		}
	}
	return pa[0][x];
}

int dist(int x, int y){
	return level[x] + level[y] - 2*level[lca(x,y)];
}

int get_centroid(int x){
	dfs_sz(x,-1); int n = sz[x]/2;
	int p = -1;
	while(true){
		bool found = false;
		for(auto e : E[x])if(e!=p&&!die[e]){
			if( sz[e] > n ){
				found = true; p = x; x = e; break;
			}
		}
		if(!found) break;
	}
	return x;
}

void centroid_decomposition(int x, int p){
	int c = get_centroid(x);
	centpa[c] = p; die[c] = true;
	for(auto e : E[c])if(e!=p&&!die[e]){
		centroid_decomposition(e,c);
	}
}

void update_to_black(int x){
	int x0 = x;
	while(x!=-1){
		auto it = ans[x].find(dist(x,x0));
		if( it != ans[x].end() ) ans[x].erase(it);
		x = centpa[x];
	}
}
void update_to_white(int x){
	int x0 = x; 
	while(x!=-1){
		ans[x].insert(dist(x,x0));
		x = centpa[x];
	}
}

int query(int x){
	int res = INF;
	int x0 = x;
	while(x!=-1){
		if( !ans[x].empty() ){
			res = min(res,(*ans[x].begin()) + dist(x,x0));
		}
		x = centpa[x];
	}
	if( res == INF ) return -1;
	return res;
}

int main(){
	geti(N);
	rep(i,N-1){
		int a,b; geti(a,b); E[a].pb(b); E[b].pb(a);
	}
	dfs_build(1,-1,0);
	build_lca();
	centroid_decomposition(1,-1);
	geti(K);
	rep(i,K){
		int a,b; geti(a,b); 
		if( a == 1 ){
			if( color[b] == 1 ) update_to_black(b);
			else update_to_white(b);
			color[b]^=1;
		}else{
			printf("%d\n",query(b));
		}
	}
}