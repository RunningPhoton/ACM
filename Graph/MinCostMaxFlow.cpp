int head[maxn], vis[maxn], dis[maxn];
int cap[maxm], nxt[maxm], pnt[maxm], cost[maxm];
int pre[maxn], flow[maxn];
int st, ed, cnt;

void init() {
    OFF(head);
    cnt = 0;
}

void add_edge(int u, int v, int c, int w){
    pnt[cnt] = v;
    nxt[cnt] = head[u];
    cap[cnt] = c;
    cost[cnt] = w;
    head[u] = cnt++;
}

void add_edges(int u, int v, int c, int w = 0) {
    add_edge(u, v, c, w);
    add_edge(v, u, 0, -w);
}


int spfa(){
    CLR(vis); MEM(dis);
    dis[st] = 0; flow[st] = inf;
    queue<int> q;
    q.push(st);
    while (q.size()) {
        int u = q.front();q.pop();
        vis[u] = 0;
        for (int i = head[u]; ~i; i = nxt[i]) {
            int v = pnt[i];
            if (cap[i] <= 0 || dis[v] <= dis[u] + cost[i]) continue;
            dis[v] = dis[u] + cost[i];
            flow[v] = min(flow[u], cap[i]);
            pre[v] = i ^ 1;
            if (!vis[v]) q.push(v);
            vis[v] = 1;
        }
    }

//    printf("Before judge: dis[ed] = %d\n", dis[ed]);
//    printf("Parent of node 5 is %d\n", pre[5]);
    if (dis[ed] >= inf) return 0;
    int f = flow[ed], now = ed;
    while (now != st) {
//            printf("now is %d\n", now);
        int id = pre[now];
        cap[id] += f;
        cap[id ^ 1] -= f;
        now = pnt[id];
    }
//    printf("After judge: dis[ed] = %d\n", dis[ed]);

    return dis[ed];

}


int MinCostMaxFlow(){
    int res = 0, C = 1;

    while (C) {
        C = spfa();
//        printf("C = %d\n", C);
        res += C * flow[ed];
    }

    return res;
}
