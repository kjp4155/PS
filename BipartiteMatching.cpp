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
int N, M, T, K, X;
#define MAX_V 2002

vector<int> v[MAX_V];
int yx[MAX_V];
bool visited[MAX_V];

int dfs(int x){
	visited[x] = 1;
	for (auto e : v[x]){
		if (yx[e] == 0 || (visited[yx[e]] == 0 && dfs(yx[e]))){
			yx[e] = x;
			return 1;
		}
	}
	return 0;
}

int main()
{
	geti(N); geti(M);
	for (int i = 1; i <= N; i++){
		int x;
		geti(x);
		rep(j, x){
			int a;
			geti(a);
			v[i].push_back(a);
		}
	}
	memset(yx, 0, sizeof(yx));
	int ans = 0;
	for (int i = 1; i <= N; i++){
		memset(visited, 0, sizeof(visited));
		ans += dfs(i);
	}
	printf("%d", ans);
}
//
/*
bool cmp_ball(ball a, ball b) { return a.size<b.size; }
*/