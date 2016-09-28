
int n, m, cur;
ull dp[2][(1 << 10) + 5];
void update(int past, int now) {
    if(now >> m & 1) dp[cur][now ^ (1 << m)] = (dp[cur][now ^ (1 << m)] + dp[1-cur][past]);
}
int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        if(n < m) swap(n, m);
        cur = 0;
        dp[0][(1 << m) - 1] = 1;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                cur ^= 1;
                CLR(dp[cur]);
                for(int state = 0; state < 1 << m; state++) {
                    update(state, state << 1);
                    if(i && !((1 << m - 1) & state)) update(state, (state << 1) ^ (1 << m) ^ 1);
                    if(j && !(state & 1)) update(state, (state << 1) ^ 3);
                }
            }
        }
        printf("%llu\n", dp[cur][(1 << m) - 1]);
    }
	return 0;
}
