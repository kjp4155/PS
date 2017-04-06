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

#define MAXV 1050
vector<Pi> E[MAXV];

vector<Pi> edges;
int dist[MAXV];

int N,M;
int main(void)
{	
	geti(N,M);
	repp(i,M){
		int a,b,c; geti(a,b,c);
		E[a].push_back({b,c});
		edges.push_back({a,b});
	}
	int S = 1; int D = N; int delayed = 0;
	for(auto e : edges){
		int x,y; x = e.Fi; y = e.Se;
		repp(i,N) dist[i] = INF;
		dist[S] = 0;
		priority_queue<Pi,vector<Pi>,greater<Pi>> q; q.push({0,S});
		while(!q.empty()){
			Pi cu = q.top(); q.pop();
			int cur = cu.Se; int curd = cu.Fi;
			if( dist[cur] < curd ) continue;
			for(auto e : E[cur]){
				if( cur == x && e.Fi == y ) continue;
				if( dist[e.Fi] > curd + e.Se ){
					dist[e.Fi] = curd + e.Se; q.push({dist[e.Fi],e.Fi});
				}
			}
		}
		if( dist[D] == INF ) {
			cout << -1; return 0;
		}
		delayed = max(delayed,dist[D]);
	}
	int original;
	for(int i=0;i<1;i++){
		repp(i,N) dist[i] = INF;
		dist[S] = 0;
		priority_queue<Pi,vector<Pi>,greater<Pi>> q; q.push({0,S});
		while(!q.empty()){
			Pi cu = q.top(); q.pop();
			int cur = cu.Se; int curd = cu.Fi;
			if( dist[cur] < curd ) continue;
			for(auto e : E[cur]){
				if( dist[e.Fi] > curd + e.Se ){
					dist[e.Fi] = curd + e.Se; q.push({dist[e.Fi],e.Fi});
				}
			}
		}
		if( dist[D] == INF ) {
			cout << -1; return 0;
		}
		original = dist[D];
	}
	cout << delayed - original;
}


