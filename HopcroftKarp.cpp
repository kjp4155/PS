#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>
#include <assert.h>
#include <queue>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <iostream>
#include <functional>
#include <vector>
#include <stack>

using namespace std;
typedef long long ll;
typedef pair<int, int> Pi;
typedef pair<long long, long long> Pll;

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

#define geti(X) scanf("%d",&X)

#define INF 987654321
#define NIL 0

int gcd(int a, int b){
	if (b == 0) return a;
	return gcd(b, a%b);
}
#define MAX_V 20010
int N, M, K, X, V, T;

#define MAXM 5005
#define MAXN 5005
int w[5005];
int l[5005];
vector<int> Edge[5005];
//M: left nodes, N: right Nodes
//pairs
int pairL[MAXM], pairR[MAXN];
// dist[u] stores distance of left side vertices
// dist[u] is one more than dist[u'] if u is next
// to u'in augmenting path
int dist[MAXM];

//return true if augmenting path exists
bool bfs(){
	queue<int> Q;
	//find free node on left and add to queue
	for (int u = 1; u <= M; u++){
		if (pairL[u] == 0){
			dist[u] = 0;
			Q.push(u);
		}
		else dist[u] = INF;
	}

	dist[0] = INF;

	while (!Q.empty()){
		int u = Q.front(); Q.pop();

		// If this node is not NIL and can provide a shorter path to NIL
		if (dist[u] < dist[0]){
			for (auto v : Edge[u]){
				// If pair of v is not considered so far
                // (v, pairV[V]) is not yet explored edge.
				if (dist[pairR[v]] == INF){
					dist[pairR[v]] = dist[u] + 1;
					Q.push(pairR[v]);
				}
			}
		}
	}
	// If we could come back to NIL using alternating path of distinct
	// vertices then there is an augmenting path
	return (dist[0] != INF);
}

// Returns true if there is an augmenting path beginning with free vertex u
bool dfs(int u){
	if (u != 0){
		for (auto v : Edge[u]){
			// Follow the distances set by BFS
			if (dist[pairR[v]] == dist[u] + 1){
				// If dfs for pair of v also returns true
				// Modify Matching set 
				if (dfs(pairR[v]) == true){
					pairR[v] = u;
					pairL[u] = v;
					return true;
				}
			}
		}
		// If there is no augmenting path beginning with u.
		dist[u] = INF;
		return false;
	}
	return true;
}

int hopcroftKarp(){
	//Ininitialize node 0 as pair of all verticies
	memset(pairL, 0, sizeof pairL);
	memset(pairR, 0, sizeof pairR);
	memset(dist, 0, sizeof dist);
	int result = 0;

	// Keep updating the result while there is an
	// augmenting path.
	while (bfs()){
		for (int u = 1; u <= M; u++){
			// If current vertex is free and there is
			// an augmenting path from current vertex
			if (pairL[u] == 0 && dfs(u)) result++;
		}
	}
	return result;
}

int main()
{
	geti(T);
	while (T--){
		geti(N);
		rep(i, 5005){
			Edge[i].clear();
		}
		repp(i, N){
			geti(w[i]); geti(l[i]);
		}

		//Simple edge-making step
		repp(i, N){
			repp(j, N){
				if (i == j) continue;

				if (w[i] >= w[j] && l[i] >= l[j]){
					Edge[j].push_back(i);
				}
			}
		}
		//#of right node is same with left
		M = N;

		cout << N - hopcroftKarp() << endl;


	}

}