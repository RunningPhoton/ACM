map <ll, ll> mp;
map <ll, ll> :: iterator iter;
ll Random(ll n) {
	return ((double) rand() / RAND_MAX * n + 0.5);
}
ll q_mul(ll a, ll b, ll mod) {
	ll ans = 0;
	while(b) {
		if(b & 1) ans = (a + ans) % mod;
		b >>= 1;
		a = (a + a) % mod;
	}
	return ans;
}
ll q_pow(ll a, ll b, ll mod) {
	ll ret = 1;
	while(b) {
		if(b & 1) ret = q_mul(ret, a, mod);
		b >>= 1;
		a = q_mul(a, a, mod);
	}
	return ret;
}
bool witness(ll a, ll n) {
	ll d = n - 1;
	while(d % 2 == 0) d >>= 1;
	ll t = q_pow(a, d, n);
	while(d != n - 1 && t != 1 && t != n - 1) {
		t = q_mul(t, t, n);
		d <<= 1;
	}
	return t == n - 1 || d & 1;
}
bool Isprime(ll p, ll n) {
	if(n == 2) return true;
	if(n < 2 || !(n & 1)) return false;
	int cnt = 20;
	while(cnt--) {
		ll base = Random(n - 2) + 1;
		if(!witness(base, p)) return false;
	}
	return true;
}
ll pollard_rho(ll n, ll c) {
	ll x, y, d, i = 1, k = 2;
	x = Random(n - 2) + 1;
	y = x;
	while(1) {
		i++;
		x = (q_mul(x, x, n) + c) % n;
		d = __gcd(y - x, n);
		if(1 < d && d < n) return d;
		if(y == x) return n;
		if(i == k) {
			y = x;
			k <<= 1;
		}
	}
}
// 分解n，c是任意传入的一个数，分解的数放在mp里面
void find(ll n, ll c) {
	if(n == 1) return;
	if(Isprime(n, n)) {
		mp[n]++;
		return;
	}
	ll p = n;
	while(p >= n)
		p = pollard_rho(p, c--);
	find(p, c);
	find(n / p, c);
}