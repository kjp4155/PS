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
#include <deque>

using namespace std;
typedef long long ll;
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
#define IINF 87654321987654321
int N,M,x;

// Suffix Array Impelementation from
// Competitive Programming, Steven Halim and Felix Halim, 2010
// page 396 ~ 397
// Make sure to add !, #, $, %, & at the end of input string
class SuffixArray{
public:
	int n;
	string s; 
	vector<int> rank, temprank, sa, tempsa, c;
	vector<int> lcp;
	SuffixArray(string _s){
		n = _s.size(); s = _s;
		rank.resize(n); temprank.resize(n); sa.resize(n); tempsa.resize(n);
		lcp.resize(n);
		constructSA();
		constructLCP();
	}

	void countingSort(int k){
		int sum = 0, maxi = max(270, n); //ASCII 256 
		c.clear(); c.resize(maxi+10);
		for(auto& e : c ) e = 0;
		for(int i=0; i<n; i++) c[ i+k<n ? rank[i+k] : 0 ] ++;
		for(int i=0; i<maxi; i++){
			int t = c[i]; c[i] = sum; sum += t;
		}
		for(int i=0; i<n; i++) tempsa[ c[ sa[i]+k < n ? rank[sa[i]+k] : 0 ] ++ ] = sa[i];
		for(int i=0; i<n; i++) sa[i] = tempsa[i];
	}


	void constructSA(){
		for(int i=0; i<n; i++) rank[i] = s[i];
		for(int i=0; i<n; i++) sa[i] = i;
		for(int k=1; k<n; k<<=1){
			countingSort(k);
			countingSort(0);
			int r = 0;
			temprank[sa[0]] = 0;
			for(int i=1; i<n; i++){
				temprank[sa[i]] = (rank[sa[i]] == rank[sa[i-1]] && rank[sa[i]+k] == rank[sa[i-1]+k] ) ? r : ++r;
			}
			for(int i=0; i<n; i++) rank[i] = temprank[i];
			if( rank[sa[n-1]] == n-1 ) break;
		}
	}


	// lcp Implementation from
	// http://m.blog.naver.com/dark__nebula/220419358547
	void constructLCP(){
		int h = 0;
		for(int i=0;i<n;i++){
			if( rank[i] ){
				int j = sa[rank[i]-1];
				while( s[i+h] == s[j+h] ) h++;
				lcp[rank[i]] = h;
			}
			if( h > 0 ) h--;
		}
	}

};


int main(){
 	string s; cin >> s;
 	SuffixArray sa(s);

 	for(int i=0;i<sz(s);i++){
 		printf("%d %d\n",sa.sa[i], sa.lcp[i]);
 	}
}