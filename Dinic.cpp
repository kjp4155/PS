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
#define IINF 987654321987654321LL

#define MAXN 100500

struct MaxFlowDinic{
	struct Edge{
		// next, inv, residual
		int to, inv; ll res;
	};

	int n;
	vector<vector<Edge>> graph;

	vector<int> lev,work;
	
	void init(int x){
		n = x+10;
		graph.resize(x+10);
		lev.resize(n); work.resize(n);
	}

	void make_edge(int s, int e, ll cap, ll caprev = 0){
		Edge forward = {e, (int)graph[e].size(), cap};
		Edge backward = {s, (int)graph[s].size(), caprev};
		graph[s].push_back(forward);
		graph[e].push_back(backward);
	}

	bool bfs(int source, int sink){
		queue<int> q;
		for(auto& e : lev) e = -1;
		lev[source] = 0; q.push(source);
		while(!q.empty()){
			int cur = q.front(); q.pop();
			for(auto e : graph[cur]){
				if(lev[e.to]==-1 && e.res > 0){
					lev[e.to] = lev[cur]+1;
					q.push(e.to);
				}
			}
		}
		return lev[sink] != -1;
	}

	ll dfs(int cur, int sink, ll flow){
		if( cur == sink ) return flow;
		for(int &i = work[cur]; i < (int)graph[cur].size(); i++){
			Edge &e =  graph[cur][i];
			if( e.res == 0 || lev[e.to] != lev[cur]+1 ) continue;
			ll df = dfs(e.to, sink, min(flow, e.res) );
			if( df > 0 ){
				e.res -= df;
				graph[e.to][e.inv].res += df;
				return df;
			}
		}
		return 0;
	}


	ll solve( int source, int sink ){
		ll ans = 0;
		while( bfs(source, sink) ){
			for(auto& e : work) e = 0;
			while( true ){
				ll flow = dfs(source,sink,54321987654321LL);
				if( flow == 0 ) break;
				ans += flow;
			}
		}
		return ans;
	}

};

int N;
int main(void){
	//ios::sync_with_stdio(false);
	scanf("%d\n",&N);
	MaxFlowDinic mf;
	mf.init(50);
	rep(i,N){
		char a,b; int x;
		scanf("%c %c %d\n",&a,&b,&x);
		mf.make_edge(a-'A',b-'A',x);
	}

	cout << mf.solve('A'-'A','Z'-'A');


}