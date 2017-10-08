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

#define Fi first
#define Se second
#define pb(x) push_back(x)
#define sz(x) (int)x.size()
#define rep(i, n) for(int i=0;i<n;i++)
#define all(x) x.begin(), x.end()

#define ABS(x) (((x) > 0 ) ? (x) : (-(x)))
#define MAX2(x, y) (((x) > (y)) ? (x) : (y))
#define MIN2(x, y) (((x) < (y)) ? (x) : (y))

#define MAX3(x, y, z) ( (x) > (y)  ? ( (x) > (z) ? (x) : (z)  ) : ( (y) > (z) ? (y) : (z) )  )
#define MIN3(x, y, z) ( (x) < (y)  ? ( (x) < (z) ? (x) : (z)  ) : ( (y) < (z) ? (y) : (z) )  )
#define MID3(val1,val2,val3) MAX2(MIN2(MAX2(val1,val2),val3),MIN2(val1,val2))

#define geti(X) scanf("%d",&X)

#define INF 987654321


int gcd(int a, int b){
	if (b == 0) return a;
	return gcd(b, a%b);
}
int N, M, T, K, X, V;
#define MAX_V 100005
#define MAX_LOG_V 20
vector<int> Edge[MAX_V];
int root;
int parent[MAX_LOG_V][MAX_V];

int depth[MAX_V];

void dfs(int v, int p, int d){
	depth[v] = d;
	parent[0][v] = p;
	for (int i = 0; i < Edge[v].size(); i++){
		if (Edge[v][i] != p) dfs(Edge[v][i], v, d + 1);
	}
}

int lca(int u, int v){
	//find LCA

	//find common depth
	if (depth[u] > depth[v]) swap(u, v);
	for (int k = 0; k < MAX_LOG_V; k++){
		if (1 << k & (depth[v] - depth[u])) v = parent[k][v];
	}
	//printf("%d %d\n", u, v);
	if (u == v) return v;
	//find LCA by binary search
	for(int k = MAX_LOG_V - 1; k >= 0; k--){
		if (parent[k][u] != parent[k][v]){
			u = parent[k][u];
			v = parent[k][v];
		}
	}
	return  parent[0][u];
}

int main()
{
	//freopen("in.txt", "r", stdin);
	geti(V); 
	rep(i,V-1){
		int a, b;
		geti(a); geti(b);
		Edge[a].push_back(b);
		Edge[b].push_back(a);
	}

	//Initialize parent[0] & depth
	root = 1;
	dfs(root, -1, 0);
	//Initialize parents
	for (int k = 0; k + 1 < MAX_LOG_V; k++){
		for (int v = 1; v <= V; v++){
			if (parent[k][v] < 0) parent[k + 1][v] = -1;
			else parent[k + 1][v] = parent[k][parent[k][v]];
		}
	}

	geti(M);
	while (M--){
		int u, v;
		geti(u); geti(v);
		printf("%d\n", lca(u, v));

	}

}
//
/*
bool cmp_ball(ball a, ball b) { return a.size<b.size; }
*/