const int N = 5e5 + 10, INF = 0x3f3f3f3f, MOD = 1004535809;
const int G = 3, P = 1004535809; // MOD的原根,当且仅当 g^(MOD-1) = 1 % MOD

typedef long long ll;

ll Pow(ll x, ll n) {
    ll ret = 1;
    for(; n; n >>= 1) {
        if(n & 1) ret = ret * x % P;
        x = x * x % P;
    }
    return ret;
}

ll A[N], B[N];
void rader(ll* y, int len) {
    for(int i = 1, j = len / 2; i < len - 1; i++) {
        if(i < j) swap(y[i], y[j]);
        int k = len / 2;
        while(j >= k) {j -= k; k /= 2;}
        if(j < k) j += k;
    }
}
void ntt(ll* y, int len, int op) {
    rader(y, len);
    for(int h = 2; h <= len; h <<= 1) {
        ll wn = Pow(G, (P - 1) / h);
        if(op == -1) wn = Pow(wn, P - 2);
        for(int j = 0; j < len; j += h) {
            ll w = 1;
            for(int k = j; k < j + h / 2; k++) {
                ll u = y[k];
                ll t = w * y[k + h / 2] % P;
                y[k] = (u + t) % P;
                y[k + h / 2] = (u - t + P) % P;
                w = w * wn % P;
            }
        }
    }
    if(op == -1) {
        ll inv = Pow(len, P - 2);
        for(int i = 0; i < len; i++) y[i] = y[i] * inv % P;
    }
}

ll f[N], g[N];


// dp[i] = (i-1)! * sigma(a[j] * b[i-1-j])
void cdq(int l, int r) {
    if(l == r) return;
    int mid = (l + r) >> 1;
    cdq(l, mid);

    int len = 1;
    while(len <= r - l + 1) len <<= 1;
    for(int i = 0; i < len; i++) {
        A[i] = a[i];
        B[i] = (l + i <= mid ? finv[l + i] * f[l + i] % P : 0);
    }
    ntt(A, len, 1);
    ntt(B, len, 1);
    for(int i = 0; i < len; i++) A[i] = A[i] * B[i] % P;
    ntt(A, len, -1);

    for(int i = mid + 1; i <= r; i++) {
        f[i] += fact[i - 1] * A[i - l - 1] % P;
        f[i] %= P;
    }
    cdq(mid + 1, r);
}