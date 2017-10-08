ll q = 1000000007;

ll modPow(int x, int n, int m){
	ll a = x; ll res = 1;
	while(n>0){
		if( n&1 ) res = (res*a)%m;
		a = (a*a)%m;
		n/=2;
	}
	return res;
}

int inv(int a, int m){
	return modPow(a,m-2,m);
}