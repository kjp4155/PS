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

int N,M,K,T;

// KMP code from baekjoon
// https://gist.github.com/Baekjoon/8d3e2a1b93e59879011f
vector<int> preprocess(string p){
	int m = p.size();
	vector<int> fail(m);
	fail[0] = 0; int j = 0;
	for(int i=1;i<m;i++){
		while(j>0&&p[i]!=p[j]) j = fail[j-1];
		if( p[i] == p[j] ){
			fail[i] = j+1; j++;
		}else{
			fail[i] = 0;
		}
	}
	return fail;
}

vector<int> kmp(string s, string p){
	auto fail = preprocess(p);
	vector<int> ans; int n = s.size(), m = p.size();
	int j = 0;
	for(int i=0;i<n;i++){
		while(j>0 && s[i]!=p[j]) j = fail[j-1];
		if( s[i] == p[j] ){
			if( j == m-1 ){
				ans.pb(i-m+1); j = fail[j];
			}else{
				j++;
			}
		}
	}
	return ans;
}

int main(void){
	string s,p;
	getline(cin,s); getline(cin,p);
	vector<int> ans = kmp(s,p);
	printf("%d\n",ans.size());
	for(auto e : ans) printf("%d ",e+1);
}
