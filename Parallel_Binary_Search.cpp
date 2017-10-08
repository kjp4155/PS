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

#define MAXN 100500
int N,M,K,Q;

vector<Pi> edge[1000500];
int pa[MAXN]; int sz[MAXN];

// each query's answer
Pi ans[MAXN];
// each query's possible answer range for binary search
int low[MAXN], high[MAXN];
// focus[x] : list of query # where it's mid value is x
vector<int> focus[1000500];

int find(int x){
	if( x == pa[x] ) return x;
	return pa[x] = find(pa[x]);
}
int x[MAXN], y[MAXN];

void uni(int a, int b){
	a = find(a); b = find(b);
	if( a == b ) return;
	pa[a] = b;
	sz[b] += sz[a];
}

int main(void){
	//ios::sync_with_stdio(false);
	geti(N,M);
	int C = -1;
	repp(i,M){
		int a,b,c; geti(a,b,c);
		edge[c].push_back({a,b});
		C = max(C, c);
	}

	geti(Q);
	repp(i,Q){
		int a,b;
		geti(a,b); x[i] = a; y[i] = b;
		ans[i] = {INF,-1};
		// Initially, every query has answer in [0,C] range
		low[i] = 0; high[i] = C;
	}

	bool changed = true;
	while( changed ){
		changed = false;
			
		// Clear variables
		rep(i,C+1) focus[i].clear();
		repp(i,N) pa[i] = i, sz[i] = 1;
		
		// Put each query into corresponding focus group
		repp(i,Q){
			if( low[i] > high[i] ) continue;
			focus[ (low[i] + high[i])/2 ].push_back(i);
		}

		// for every time 0~C
		for(int k=0;k<=C;k++){
			// perform action of that time
			for(auto e : edge[k]) uni(e.Fi,e.Se);

			// for each focus group
			// determine it's answer & next position
			for(auto e : focus[k]){
				changed = true;
				int a = x[e]; int b = y[e];
				if( find(a) == find(b) ){
					ans[e].Fi = min(ans[e].Fi, k);
					ans[e].Se = sz[find(a)];
					high[e] = k-1;
				}	
				else{
					low[e] = k+1;
				}
			}
		}
	}

	repp(i,Q){
		if( ans[i].Fi == INF ) printf("%d\n",-1);
		else printf("%d %d\n",ans[i].Fi, ans[i].Se);
	}

}