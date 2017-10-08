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
#define IINF 7654321987654321
#define MOD 1000

int N,M,K,T;

// https://algospot.com/wiki/read/Manacher%27s_algorithm
// finds radius of longest palindrome centered at s[i]
// If you also want to find even-length paindromes, use dummy characters
// baab -> #b#a#a#b#
vector<int> ManacherAlgorithm(string s){
	int n = (int) s.size();
	int p = -1, r = -1;
	vector<int> A(n);
	for(int i=0;i<n;i++){

		if( r < i ){
			A[i] = 0;
			int j = 0;
			while( i + A[i] < n && i - A[i] >= 0 && s[ i+A[i] ] == s[ i-A[i] ] ) A[i]++;
			A[i]--;
		}
		else{
			A[i] = min( A[2*p - i] , r-i );
			while( i + A[i] < n && i - A[i] >= 0 && s[ i+A[i] ] == s[ i-A[i] ] ) A[i]++;
			A[i]--;
		}

		// update r
		if( r < i + A[i] ){
			r = i + A[i];
			p = i;
		}
	}
	return A;
}


int main(){

	// https://www.acmicpc.net/problem/14444
	// find longest palindrome's length in string

	string s; cin >> s;

	// for odd length palindromes
	string s1 = s; 

	// for even length palindromes
	// generate #b#a#n#a#n#a#
	string s2 = "#";
	for(int i=0;i<sz(s);i++){
		s2 += s[i];
		s2 += "#";
	}

	auto v1 = ManacherAlgorithm(s1);
	auto v2 = ManacherAlgorithm(s2);

	int ans = 1;
	for(auto e : v1 ){
		ans = max(ans , 2*e+1);
	}

	for(auto e : v2){
		ans = max(ans, e);
	}

	cout << ans;

}


