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
#define MAX_V 20010
int N, M, T, K, X, V;


vector<int> Edge[MAX_V];
vector<int> rEdge[MAX_V];
vector<int> vs;

bool vis[MAX_V];
int cmp[MAX_V];
set<int> printSet[MAX_V];

void addEdge(int from, int to){
	Edge[from].push_back(to);
	rEdge[to].push_back(from);
}

void dfs(int v){
	vis[v] = true;
	for (int i = 0; i < Edge[v].size(); i++){
		if (!vis[Edge[v][i]]) dfs(Edge[v][i]);
	}
	vs.push_back(v);
}

void rdfs(int v, int k){
	vis[v] = true;
	cmp[v] = k;
	printSet[k].insert(v);
	for (int i = 0; i < rEdge[v].size(); i++){
		if (!vis[rEdge[v][i]]) rdfs(rEdge[v][i], k);
	}
}

bool cmp1(set<int>& a, set<int>& b) {
	return *a.begin() < *b.begin();
}



int main()
{
	//freopen("in.txt", "r", stdin);
	geti(V); geti(M);
	int cnt = 0;
	while (M--){
		int a, b;
		scanf("%d%d", &a, &b);
		if (a > 0 && b > 0 ){
			addEdge(a + V, b);
			addEdge(b + V, a);

		}
		else if (a > 0 && b < 0){
			b = -b;
			addEdge(a + V, b + V);
			addEdge(b , a);
		}
		else if (a < 0 && b > 0){
			a = -a;			
			addEdge(a, b);
			addEdge(b + V, a + V);

	
		}
		else{
			a = -a; b = -b;
			addEdge(a, b + V);
			addEdge(b, a + V);

		}
	}
	
	memset(vis, false, sizeof(vis));
	for (int i = 1; i <= 2*V; i++){
		if (!vis[i]) dfs(i);
	}


	memset(vis, false, sizeof(vis));
	int k = 0;
	for (int i = vs.size()-1; i >= 0 ; i--){
		if (!vis[vs[i]]) rdfs(vs[i],k++);
	}

	
	for (int i = 1; i <= V; i++){
		if (cmp[i] == cmp[V + i]){
			printf("0\n");
			return 0;
		}
	}
	printf("1\n");

	for (int i = 1; i <= V; i++){
		if (cmp[i] > cmp[V + i]){
			printf("1 ");
		}
		else printf("0 ");
	}
}