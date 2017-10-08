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

int N,M,T,K,V;

typedef struct Point{
	int x,y;
	bool operator<(const Point& l) const{
		if( y == l.y ) return x < l.x;
		return y < l.y;
	}
	bool operator==(const Point& l) const{
		return (x==l.x)&&(y==l.y);
	}
} Point;

bool cmp(const Point& l, const Point& r){
	if(l.x == r.x ) return l.y < r.y;
	return l.x < r.x;
}

int dist(Point& l, Point& r ){
	return (l.x-r.x)*(l.x-r.x) + (l.y-r.y)*(l.y-r.y);
}

int main(void)
{
	geti(N); vector<Point> v(N);
	for(int i=0;i<N;i++){
		int x ,y; geti(x,y); v[i].x = x; v[i].y = y;
	}
	sort(all(v),cmp);
	int ans = dist(v[0],v[1]); int left = 0;
	set<Point> possible; possible.insert(v[0]); possible.insert(v[1]);
	
	for(int i=2;i<N;i++){
		while( (v[i].x - v[left].x)*(v[i].x - v[left].x ) > ans ){
			possible.erase(v[left]);
			left++;
		}
		int d = (int) sqrt(ans) + 1;
		auto bottom = possible.lower_bound({-100000,v[i].y-d});
		auto top = possible.upper_bound({100000,v[i].y+d});
		for(auto it = bottom; it != top; it++){
			Point cur = *it;
			if( dist(v[i],cur) < ans ) ans = dist(v[i],cur);
		}
		possible.insert(v[i]);
	}
	cout << ans;
}

/*
 
 */