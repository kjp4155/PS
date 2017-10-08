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

int N,L,M;

map<set<int>,int> grundy;
map<ll,set<int>> mp;

int get_grundy(set<int> x){
	// base case
	if( sz(x) == 0 ) return 0;
	if( grundy.find(x) != grundy.end() ) return grundy[x];
	
	set<int> S;
	int res = 0;

	auto iter = x.end(); iter--;
	int mx = *iter;

	// transition : which k to select
	for(int i=1;i<=mx;i++){
		set<int> nxt;
		for(auto e : x){
			if( e < i ) nxt.insert(e);
			else if( e == i ) continue;
			else nxt.insert(e-i); 
		}
		S.insert(get_grundy(nxt));
	}

	// find mex and return
	while( S.find(res) != S.end() ) res++;
	grundy[x] = res;
	return res;
}
int main(void){
	int n; geti(n);

	// Simple prime factorization
	rep(i,n){
		ll x; scanf("%lld",&x);
		for(ll i=2;i*i<=x;i++){
			if( x>0 && x%i == 0 ){
				int cnt = 0;
				while( x>0 && x%i == 0 ){
					cnt++; x/= i;
				}
				mp[i].insert(cnt);
			}
		}
		if( x > 1 ){
			mp[x].insert(1);
		}
	}

	int res = 0;
	for(auto e : mp){
		res ^= get_grundy(e.Se);
	}	

	if( res == 0 ) printf("Arpa");
	else printf("Mojtaba");
}