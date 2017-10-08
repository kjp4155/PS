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

vector<int> E[1005], rE[1005];
bool vis[1005], rvis[1005];
int xy[1005], yx[1005];
set<int> L,R,Tl,Tr,X;
int dfs(int x){
	vis[x] = true;
	for(auto e : E[x] ){
		if( yx[e] == 0 || (vis[yx[e]] == false && dfs(yx[e]))){
			yx[e] = x; xy[x] = e;
			return 1;
		}
	}
	return 0;
}

int main(){
	geti(N,M);
	repp(i,N){
		int n; geti(n);
		while(n--){
			int x; geti(x);
			E[i].pb(x); rE[x].pb(i);
		}
	}
	int ans = 0;
	repp(i,N){
		memset(vis,0,sizeof vis);
		ans += dfs(i);
	}
	cout << ans << endl;
	repp(i,N){
		if( xy[i] != 0 ) L.insert(i);
		if( xy[i] == 0 ) X.insert(i);
	}
	repp(i,M){
		if( yx[i] != 0 ) R.insert(i);
	}

	memset(vis,0,sizeof vis); memset(rvis,0,sizeof rvis);
	//http://makesource.tistory.com/entry/%EA%B7%B8%EB%9E%98%ED%94%84-%EA%B4%80%EB%A0%A8
	for(auto x : X){
		queue<Pi> q;
		q.push({x,-1});
		vis[x] = true;
		while(!q.empty()){
			int v = q.front().first; int c = q.front().second; q.pop();
			if( c == -1 ) Tl.insert(v);
			if( c == 1 ) Tr.insert(v);
			if( c == -1 ){
				//선택되지 않은 간선을 통해 R로 가야됨
				for(auto e : E[v] ){
					if( yx[e] == x || rvis[e]) continue;
					q.push({e,1});
					rvis[e] =  true;
				}
			}else if( c == 1 ){
				//선택된 간선을 통해 L로 가야됨
				for(auto e : rE[v] ){
					if( xy[e] != v || vis[e]) continue;
					q.push({e,-1});
					vis[e] = true;
				}
			}
		}
	}
	for(auto e : Tl ){
		L.erase(e);
	}
	set<int> ansr;
	for(auto e : Tr ){
		if( R.find(e) != R.end() ) ansr.insert(e);
	}

	printf("%d ",L.size());
	for(auto e : L ) printf("%d ",e);
	printf("\n");

	printf("%d ",ansr.size());
	for(auto e : ansr ) printf("%d ",e);
}

