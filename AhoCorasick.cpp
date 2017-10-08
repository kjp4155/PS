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

#define MAXN 100500

struct AhoCorasick{
	struct Node{
		int fail;
		vector<int> output;
		int children[26];

		Node(){
			for(int i=0;i<26;i++) children[i] = -1;
			fail = -1;
		}
	};

	vector<Node> trie;
	int new_node(){
		Node x;
		trie.push_back(x);
		return (int)trie.size()-1;
	}

	void add(int node, string &s, int idx, int string_num){	
		//cout << node << " " << idx << endl;	
		if( idx == s.size() ){
			trie[node].output.push_back(string_num);
			return;
		}
		int c = s[idx] - 'a';
		if( trie[node].children[c] == -1 ){
			int next = new_node();
			trie[node].children[c] = next;
		}

		add(trie[node].children[c], s, idx+1, string_num);
	}

	void build(vector<string> v){
		int root = new_node();
		for(int i=0;i<v.size();i++){
			add(root,v[i],0,i);
		}

		queue<int> q;
		q.push(root); trie[root].fail = root;
		while( !q.empty() ){
			int cur = q.front(); q.pop();
			for(int i=0;i<26;i++){
				int next = trie[cur].children[i];
				if( next == -1 ) continue;
				
				// build fail
				if( cur == root ){
					trie[next].fail = root;
				}
				else{
					int x = trie[cur].fail;
					while( x != root && trie[x].children[i] == -1 ) x = trie[x].fail;
					if( trie[x].children[i] != -1 ) x = trie[x].children[i];
					trie[next].fail = x;
				}
				// build output
				int f = trie[next].fail;
				for(auto e : trie[f].output) trie[next].output.push_back(e);
				q.push(next);
			}
		}
	}

	vector<Pi> find(string s){
		int n = (int) s.size();
		int cur = 0, root = 0;
		vector<Pi> ans;
		for(int i=0;i<n;i++){
			int c = s[i]-'a';
			while( cur != root && trie[cur].children[c] == -1 ) cur = trie[cur].fail;
			if( trie[cur].children[c] != -1 ) cur = trie[cur].children[c];

			for(auto e : trie[cur].output){
				ans.push_back({e,i});
			}

		}
		return ans;
	}

};
// https://www.acmicpc.net/problem/9250
int main(void){
	ios::sync_with_stdio(false);
	AhoCorasick aho;
	int n,m; cin >> n;
	vector<string> list;
	rep(i,n){
		string x; cin >> x;
		list.push_back(x);
	}	
	aho.build(list);

	cin >> m;
	rep(i,m){
		string s; cin >> s;
		vector<Pi> ans = aho.find(s);
		if( ans.size() == 0 ) cout << "NO" << endl;
		else cout << "YES" << endl;
	}

}
