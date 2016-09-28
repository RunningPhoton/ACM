int mu[maxn];
int primes[maxn], tot = 0;
int vis[maxn];
ll sum[maxn];
void Mobius(int n) {
	mu[1] = 1;
	tot = 0;
	for(int i = 2; i <= n; i++) {
		if(!vis[i]) {
			mu[i] = -1;
			primes[tot++] = i;
		}
		for(int j = 0; j < tot && i * primes[j] <= n; j++) {
			vis[i*primes[j]] = 1;
			if(i % primes[j] != 0) mu[i*primes[j]] = -mu[i];
			else {
				mu[i*primes[j]] = 0;
				break;
			}
		}
	}
	for(int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + mu[i];
    }
}
// 求（a,b）互质的点对数
ll solve(ll a, ll b) {
    ll ans = 0;
    if(a > b) swap(a, b);
    for(ll i = 1, la = 0; i <= a; i = la + 1) {
        la = min(a / (a / i), b / (b / i));
        ans += (ll)(sum[la] - sum[i - 1]) * (a / i) * (b / i);
    }
    return ans;
}
