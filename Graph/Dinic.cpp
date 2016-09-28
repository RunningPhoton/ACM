int Lv[maxn], head[maxn], st, ed, cnt;
int cap[maxm], pnt[maxm], nxt[maxm], cur[maxn];

void add_edge(int u, int v, int c) {
    pnt[cnt] = v;
    nxt[cnt] = head[u];
    cap[cnt] = c;
    head[u] = cnt++;
}

void add_edges(int u, int v, int c) {
    add_edge(u, v, c);
    add_edge(v, u, c);
}

bool bfs(){
    CLR(Lv);
    Lv[st] = 1;
    queue<int> q;
    q.push(st);
    while (q.size()) {
        int u = q.front();q.pop();
        for (int i = head[u]; ~i; i = nxt[i]) {
            int v = pnt[i];
            if (Lv[v] || cap[i] <= 0) continue ;
            Lv[v] = Lv[u] + 1;
            q.push(v);
        }
    }
    return Lv[ed];
}

int dfs(int u, int f) {
    if (f == 0 || u == ed) return f;
    int left = f;
    for (int i = head[u]; ~i; i = nxt[i]) {
//        cur[u] = i;
        int v = pnt[i];
        if (Lv[v] != Lv[u] + 1 || cap[i] <= 0) continue ;
        int d = dfs(v, min(cap[i], left));
        if (d > 0) {
            cap[i] -= d;
            cap[i ^ 1] += d;
            left -= d;
            if (left == 0) break;
        } else Lv[v] = 0;
    }
    return f - left;
}

int Max_Flow(){
    int res = 0;
    while (bfs()) {
//        for (int i = 0; i <= n; i++)
//            cur[i] = head[i];
        res += dfs(st, inf);
    }
    return res;
}

void init() {
    OFF(head);
    cnt = 0;
}
