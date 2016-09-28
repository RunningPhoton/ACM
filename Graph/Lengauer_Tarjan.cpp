int semi[maxn], idom[maxn], par[maxn], best[maxn];
int dfn[maxn], id[maxn], fa[maxn], tot, n, m;

struct Graph {
	struct Edge {
		int to, next;
	} edge[maxm];

	int head[maxn], ecnt;

	void add(int u, int v) {
		edge[ecnt].to = v;
		edge[ecnt].next = head[u];
		head[u] = ecnt++;
	}

	void init() {
		ecnt = 0; 
		memset(head, -1, sizeof head);
	}
}g1, g2, dom;

void init() {
	tot = 0;
	memset(dfn, 0, sizeof dfn);
	memset(semi, 0, sizeof semi);
	memset(idom, 0, sizeof idom);
	for(int i = 1; i <= n; i++) par[i] = best[i] = i;
	g1.init(), g2.init(), dom.init();
}
int les(int x, int y) { return dfn[semi[x]] < dfn[semi[y]] ? x : y; }

int find(int x) {
	if(par[x] == x) return x;
	int y = find(par[x]);
	best[x] = les(best[x], best[par[x]]);
	return par[x] = y;
}

void dfs(int u) {
	dfn[u] = ++tot; id[tot] = u;
	for(int i = g1.head[u]; ~i; i = g1.edge[i].next) {
		int v = g1.edge[i].to;
		if(dfn[v]) continue;
		dfs(v); fa[v] = u;
	}
}

void tarjan() {
	dfn[0] = inf;
	for(int k = tot; k; k--){
		int x = id[k];
		for(int i = g2.head[x]; ~i; i = g2.edge[i].next){
			int y = g2.edge[i].to; 
			if (!dfn[y]) continue;
			if (dfn[y] < dfn[x]) {
				if (dfn[y] < dfn[semi[x]]) semi[x] = y;
			} else {
				find(y); semi[x] = semi[les(x, best[y])];
			}
		}
		dom.add(semi[x],x);
		for (int i = dom.head[x]; ~i; i = dom.edge[i].next){
			int y = dom.edge[i].to; find(y);
			if(semi[best[y]] != x) idom[y] = best[y];
			else idom[y] = x;
		}
		for(int i = g1.head[x]; ~i; i = g1.edge[i].next)
			if(fa[g1.edge[i].to] == x) par[g1.edge[i].to] = x;
	}	
	for(int i = 2; i <= tot; i++){
		int x = id[i];
		if (idom[x] != semi[x]) idom[x] = idom[idom[x]];
	}
	idom[id[1]]=0;
}

ll dp[maxn];

ll solve(int x) {
	if(dp[x]) return dp[x]; 
	if(x == n) return dp[x] = n;
	return dp[x] = x + solve(idom[x]);
}