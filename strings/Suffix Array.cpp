char s[maxn];
int sa[maxn], c[maxn], t[maxn], t1[maxn];

void build_sa(int n, int m) {
    int *x = t, *y = t1;

    for (int i = 0; i < m; i++)  c[i] = 0;
    for (int i = 0; i < n; i++) c[x[i] = s[i]]++;
    for (int i = 1; i < m; i++) c[i] += c[i - 1];
    for (int i = n - 1; ~i; i--)  sa[--c[x[i]]] = i;

    for (int k = 1; k <= n; k <<= 1) {
        int p = 0;
        for (int i = n - k; i < n; i++) y[p++] = i;
        for (int i = 0; i < n; i++) if(sa[i] >= k) y[p++] = sa[i] - k;

        for (int i = 0; i < m; i++) c[i] = 0;
        for (int i = 0; i < n; i++) c[x[y[i]]]++;
        for (int i = 1; i < m; i++) c[i] += c[i - 1];
        for (int i = n - 1; ~i; i--) sa[--c[x[y[i]]]] = y[i];

        swap(x, y);
        p = 1; x[sa[0]] = 0;
        for (int i = 1; i < n; i++)
            x[sa[i]] = y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k] ? p - 1 : p++;
        if(p >= n) break;
        m = p;
    }

}

int Rank[maxn], height[maxn];

void Get_Height(int n){
    for (int i = 0; i < n; i++) Rank[sa[i]] = i;
    int k = 0;
    for (int i = 0; i < n; i++) {
        if(k) k--;
        int j = sa[Rank[i] - 1];
        while (s[i + k] == s[j + k]) k++;
        height[Rank[i]] = k;
    }
}
