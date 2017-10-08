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

#define MAXV 1500
int N,M,K,tc;
ll c[1000005];
ll p[1000005]; int Bsize;
typedef struct query{
	int l,r,n; ll ans;
} query;
bool cmp(query& a, query& b){
	if( a.l/Bsize == b.l/Bsize ) return a.r < b.r;
	else return a.l/Bsize < b.l/Bsize;
}
bool cmp2(query&a, query& b ){ return a.n < b.n; }
int main(void)
{
	geti(N,M); rep(i,N) scanf("%lld",p+i);
	Bsize = (int) sqrt(1.0*N);
	vector<query> q;
	rep(i,M){
		int a,b; geti(a,b); a--;b--;
		q.push_back({a,b,i});
	}
	
	sort(all(q),cmp);
	int l=0, r=-1; ll sum = 0;
	
	for(int i=0;i<q.size();i++){
		query& e = q[i];
		int ql = e.l, qr = e.r;
		while( r < qr ){
			r++;
			sum += p[r]*(2*c[p[r]]+1); c[p[r]]++;
		}
		while( r > qr ){
			sum += p[r]*(1-2*c[p[r]]); c[p[r]]--;
			r--;
		}
		while( l < ql ){
			sum += p[l]*(1-2*c[p[l]]); c[p[l]]--;
			l++;
		}
		while( l > ql ){
			l--;
			sum += p[l]*(2*c[p[l]]+1); c[p[l]]++;
		}
		e.ans = sum;
	}
	
	sort(all(q),cmp2);
	for(auto e : q ){
		printf("%lld\n",e.ans);
	}
}



