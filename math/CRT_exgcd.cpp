void exgcd(ll a, ll b, ll& d, ll& x, ll& y) {
	if(!b) {d = a; x = 1; y = 0;}
	else {exgcd(b, a%b, d, y, x); y -= x * (a / b);}
}
ll inv(ll a, ll n) { //mod n 
	ll d, x, y;
	exgcd(a, n, d, x, y);
	return d == 1 ? (x + n) % n : -1;
}
/*
x = ai(mod mi)
m1 * m2 * ... * mi = M
mi之间互素
x = sigma(ai * Mi * Mi(-1)) % M
Mi = M / mi
Mi(-1) = Mi 模mi的逆
*/
ll mul(ll a, ll b, ll M) {
    ll ret = 0;
    while(b) {
        if(b & 1) ret = (ret + a) % M;
        a = a * 2 % M;
        b >>= 1;
    }
    return ret;
}
ll CRT(ll a[], ll m[], ll n) {
	ll M = 1;
	ll ans = 0;
	for(int i = 1; i <= n; i++)
		M *= m[i];
	for(int i = 1; i <= n; i++) {
		ll Mi = M / m[i];
		ll x, y, d;
        exgcd(Mi, m[i], d, x, y);
		ans = (ans + mul(x, mul(a[i], Mi, M), M)) % M;
	}
	if(ans < 0) ans += M;
	return ans;
}
/*
当mi不互素的时候
两两合并求答案
*/
bool Merge(ll a1, ll m1, ll a2, ll m2, ll &a3, ll &m3)
{
    ll d = __gcd(m1, m2);
    ll c = a2 - a1;
    if(c % d) return false;
    c = (c % m2 + m2) % m2;
    m1 /= d;
    m2 /= d;
    c /= d;
    c *= inv(m1, m2);
    c %= m2;
    c *= m1 * d;
    c += a1;
    m3 = m1 * m2 * d;
    a3 = (c % m3 + m3) % m3;
    return true;
}

ll CRT(ll a[], ll m[], int n) {
    ll a1 = a[1];
    ll m1 = m[1];
    for(int i=2; i<=n; i++) {
        ll a2 = a[i];
        ll m2 = m[i];
        ll m3, a3;
        if(!Merge(a1, m1, a2, m2, a3, m3))
            return -1;
        a1 = a3;
        m1 = m3;
    }
    return (a1 % m1 + m1) % m1;
}