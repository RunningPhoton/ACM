int dfn[maxn], low[maxn], n, m, cnt;
int head[maxn], pnt[maxm], nxt[maxm];
int dfsnum, sccno[maxn];

stack<int> S;


void tarjan(int u) {
    dfn[u] = low[u] = ++dfsnum;
    S.push(u);
    for (int i = head[u]; ~i; i = nxt[i]) {
        int v = pnt[i];
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (!sccno[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        int x = -1;
        cnt++;
        while (x != u) {
            x = S.top();S.pop();
            sccno[x] = cnt;
        }
    }
}
