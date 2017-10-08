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

int N,M;

struct MCMF{
	struct edge{
		int to, inv, cap, flow, cost;
		int res(){
			return cap - flow;
		}
	};

	vector<vector<edge>> graph;
	vector<int> pv, pe;
	vector<int> dist, inq;
	
	void init(int x){
		graph.resize(x+10);
		for(auto& e : graph) e.resize(x+10);
		pv.resize(x+10); pe.resize(x+10);
		dist.resize(x+10);
		inq.resize(x+10);
	}

	void make_edge(int from, int to, int cap, int cost){
		//printf("%d -> %d | cost = %d\n",from,to,cost);
		edge forward = {to, (int)graph[to].size(), cap, 0, cost};
		edge backward = {from, (int)graph[from].size(), 0, 0, -cost};
		graph[from].push_back(forward);
		graph[to].push_back(backward);
	}

	int solve(int source, int sink){
		int ans = 0;
		int totalflow = 0;
		while(true){
			for(auto& e : dist) e = INF;
			for(auto& e : inq) e = 0;
			queue<int> q;
			q.push(source); inq[source] = 1;
			dist[source] = 0;

			while(!q.empty()){
				int cur = q.front(); q.pop();
				inq[cur] = 0;
				for(int i=0;i<(int)graph[cur].size();i++){
					auto& e = graph[cur][i];
					if( e.res() > 0 && dist[e.to] > dist[cur] + e.cost ){
						dist[e.to] = dist[cur] + e.cost;
						pv[e.to] = cur; pe[e.to] = i;
						if( inq[e.to] == 0 ){
							q.push(e.to); inq[e.to] = 1;
						}
					}
				}
			}

			if( dist[sink] == INF ) break;
			
			// add this limit when we don't require maxflow
			//if( dist[sink] > 0 ) break;

			int mnflow = INF;
			for( int v = sink; v != source; v = pv[v] ){
				mnflow = min( mnflow, graph[pv[v]][pe[v]].res() );
			}

			for( int v = sink; v != source; v = pv[v] ){
				int tmp = graph[pv[v]][pe[v]].inv;
				graph[pv[v]][pe[v]].flow += mnflow;
				graph[v][tmp].flow -= mnflow;
			}
			totalflow += mnflow;
			ans += dist[sink] * mnflow;
		}
		return ans;
	}

};


int main(void){

}