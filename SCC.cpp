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
#define MAX_V 10005
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
	for (auto e : Edge[v]){
		if (!vis[e]) dfs(e);
	}
	vs.push_back(v);
}

void rdfs(int v, int k){
	vis[v] = true;
	cmp[v] = k;
	printSet[k].insert(v);
	for (auto e : rEdge[v]){
		if (!vis[e]) rdfs(e, k);
	}
}

bool cmp1(set<int>& a, set<int>& b) {
	return *a.begin() < *b.begin();
}

int main()
{
	//freopen("in.txt", "r", stdin);
	geti(V); geti(M);
	while (M--){
		int a, b;
		scanf("%d%d", &a, &b);
		addEdge(a, b);
	}

	memset(vis, false, sizeof(vis));
	for (int i = 1; i <= V; i++){
		if (vis[i] == false) dfs(i);
	}


	memset(vis, 0, sizeof(vis));
	int k = 0;
	for (int i = vs.size()-1; i >= 0 ; i--){
		if (!vis[vs[i]]) rdfs(vs[i],k++);
	}

	cout << k << endl;
	sort(printSet, printSet + k, cmp1);
	for (int i = 0; i < k; i++){
		for (auto e : printSet[i]){
			printf("%d ", e);
		}
		printf("-1\n");
	}
}
//
/*
bool cmp1(set<int>& a, set<int>& b) {
return *a.begin() < *b.begin();
}
*/
