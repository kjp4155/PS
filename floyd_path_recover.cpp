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

#define geti(X) scanf("%d",&X)

#define INF 987654321
int N,M,T,K;
int p[105][105];
int m[105][105];
int main(){
	geti(N); geti(M);
	rep(i,105) rep(j,105) p[i][j] = INF;
	while(M--){
		int a,b,c; scanf("%d%d%d",&a,&b,&c);
		p[a][b] = min(p[a][b],c);
	}
	rep(i,105) p[i][i] = 0;
	rep(i,105) rep(j,105){
		if( i == j || p[i][j] == INF ) m[i][j] = -1;
		else m[i][j] = i;
	}
	repp(k,N) repp(i,N) repp(j,N){
		if( p[i][j] > p[i][k] + p[k][j] ){
			p[i][j] = p[i][k] + p[k][j];
			m[i][j] = m[k][j];
		}
	}
	
	repp(i,N){
		repp(j,N){
			if( p[i][j] == INF ) printf("0 ");
			else printf("%d ",p[i][j]);
		}
		puts("");
	}
	
	repp(i,N){
		repp(j,N){
			if( i == j || p[i][j] == INF	){
				printf("0\n"); continue;
			}
			stack<int> stk;
			stk.push(j);
			while( m[i][stk.top()] != -1 ){
				stk.push(m[i][stk.top()]);
			}
			vector<int> ans;
			while(!stk.empty()){
				ans.pb(stk.top()); stk.pop();
			}
			printf("%d ",ans.size());
			for(auto e : ans ){
				printf("%d ",e);
			}
			printf("\n");
		}
	}
	
	
}


