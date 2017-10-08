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
int N,M,T,K;
vector<int> E[100005];
bool vis[100005];
int num[100005];
int low[100005];
int scnt;
set<int> ans;
int dfs(int x, int p){
	vis[x] = true;
	int child = 0;
	num[x] = scnt++; low[x] = num[x];
	for(auto e : E[x]){
		if( e == p ) continue;
		if( !vis[e] ){
			child++;
			int l = dfs(e,x);
			if( p != -1 && l >= num[x] ) ans.insert(x);
			low[x] = min(low[x],l);
		}else{
			low[x] = min(low[x],num[e]);
		}
	}
	if( p == -1 && child >= 2 ) ans.insert(x);
	return low[x];
}


int main(){
	geti(N,M);
	while(M--){
		int a,b; geti(a,b);
		E[a].pb(b); E[b].pb(a);
	}
	scnt=1;
	repp(i,N){
		if(vis[i]==0){
			dfs(i,-1);
		}
	}
	printf("%d\n",ans.size());
	for(auto e : ans ){
		printf("%d " , e);
	}

}

