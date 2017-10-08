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
#include <deque>
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

#define geti1(X) scanf("%d",&X)
#define geti2(X,Y) scanf("%d%d",&X,&Y)
#define geti3(X,Y,Z) scanf("%d%d%d",&X,&Y,&Z)
#define geti4(X,Y,Z,W) scanf("%d%d%d%d",&X,&Y,&Z,&W)

#define GET_MACRO(_1,_2,_3,_4,NAME,...) NAME
#define geti(...) GET_MACRO(__VA_ARGS__, geti4, geti3, geti2, geti1) (__VA_ARGS__)

#define INF 987654321
#define IINF 987654321987654321
#define MAXV 3000500


#define MOD 1234567

int N,M,T,K;

// Z algorithm from http://codeforces.com/blog/entry/3107
// Calculates LCP[i] for all 0 <= i < n
vector<int> Zalgorithm(string s){
	int l=0, r=0;
	int n = (int) s.size();
	vector<int> Z(n); 
	Z[0] = n; 
	for(int i=1; i<n; i++){
		// reset and calculate again
		if( i > r ){
			l = r = i;
			while( r<n && s[r] == s[r-l] ) r++;
			r--;
			Z[i] = r-l+1;
		}

		// extend [l,r]
		else{
			int k = i-l;
			// not enough matching at position k
			if( Z[k] < r-i+1 ) Z[i] = Z[k];
			// enough matching. extend [l,r]
			else{
				l = i;
				while( r<n && s[r] == s[r-l] ) r++;
				r--;
				Z[i] = r-l+1;
			}
		}

	}
	return Z;
};

int main(){
	string s; cin >> s;
	vector<int> Z = Zalgorithm(s);
	rep(i,sz(Z)){
		printf("%d %d\n",i,Z[i]);
	}
}

