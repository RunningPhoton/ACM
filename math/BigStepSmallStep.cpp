struct Node {
	ll x, y;
};
vector <Node> G[MAX];
ll hash(ll a) {
	return a % MOD;
}
ll find(ll a) {
	ll u = hash(a);
	for (ll i = 0; i < G[u].size(); i++){
		if (G[u][i].x == a) return G[u][i].y;
	}
	return -1LL;
}
void init() {
	for (ll i = 0; i <= MOD; i++) G[i].clear();
}
ll mod_mul(ll a, ll b, ll N) {  
    ll ret = 0;
    while(b) { 
        if(b & 1) ret = (ret + a) % N;  
        a = 2 * a % N;  
        b >>= 1;  
    }  
    return ret;  
}
ll mod_pow(ll x, ll n, ll N) {  
    ll ret = 1;  
    x %= N;
    while(n) {  
        if (n & 1) ret = mod_mul(ret, x, N);  
        x = mod_mul(x, x, N);  
        n >>= 1;  
    }  
    return ret;  
}
void ex_gcd(ll a, ll b, ll& d,ll& x, ll& y){
	if (b == 0){
		d = a;
		x = 1;
		y = 0;
		return;
	}
	ex_gcd(b, a%b, d, y, x);
	y -= x * (a / b);
}
ll inv(ll a, ll N){
	ll d, x, y;
	ex_gcd(a, N, d, x, y);
	if (d == 1) return (x + N) % N;
	return -1;
}
// 大步小步算法求 a ^ x = b mod N 中的 x
ll mod_log(ll a, ll b, ll N){
	ll m = (ll)sqrt(N + 0.5);
	ll s = 1LL;
	for (ll i = 0; i <= m; i++){
		if(find(s) < 0) {
			G[hash(s)].push_back((Node){s,i});
		}
		s = mod_mul(s, a, N);
	}
	ll v = inv(mod_pow(a, m, N), N);                     //求a^m的逆元
	for (ll i = 0; i < m; i++){
		ll res = find(b);
		if (res != -1) return i * m + res;                   
		b = mod_mul(b, v, N);
	}
	return -1LL; //无解
}