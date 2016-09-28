ll F[MOD + 10];
void init(ll p) {
    F[0] = 1;
    for(int i = 1;i <= p;i++)
        F[i] = F[i-1]*i % MOD;
}

ll inv(ll a, ll m) {
    if(a == 1) return 1;
    return inv(m % a, m) * (m - m / a) % m;
}
ll lucas(ll n, ll m, ll p)
{
    ll ans = 1;
    while(n && m)
    {
        ll a = n % p;
        ll b = m % p;
        if(a < b) return 0;
        ans = ans * F[a] % p * inv(F[b] * F[a-b] % p, p) % p;
        n /= p;
        m /= p;
    }
    return ans;
}