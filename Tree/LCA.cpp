int par[20][maxn];

int LCA(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = 0; i <= 18; i++) {
        if (dep[x] - dep[y] >> i & 1) x = par[i][x];
    }

    if (x == y) return x;
    for (int i = 18; ~i; i--) {
        if (par[i][x] == par[i][y]) continue;
        x = par[i][x];
        y = par[i][y];
    }
    return par[0][x];
}

void init(){
    for (int i = 0; i <= 18; i++) {
        for (int j = 1; j <= n; j++) {
            int p = par[i][j];
            par[i + 1][j] = par[i][p];
        }
    }
}
