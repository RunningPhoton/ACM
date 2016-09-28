int head[maxn], vis[maxn], dfn[maxn], low[maxn];
int cnt, ecnt, bcnt, n, m;

void add_edge(int u, int v) {
	edge[ecnt].to = v;	
	edge[ecnt].next = head[u];
	head[u] = ecnt++;
}

map<P, int> bcc;
stack<P> Stack;

void tarjan(int fa, int u) {
	static int cnt = 0;
	dfn[u] = low[u] = ++cnt;
	int chd = 0;
	for(int i = head[u]; ~i; i = edge[i].next) {
		int v = edge[i].to;
		if(!dfn[v]) {
			chd++;
			Stack.push({u, v}); tarjan(u, v);		
			low[u] = min(low[u], low[v]);		
			if(low[v] >= dfn[u]) {
				P p; bcnt++;
				do {
					p = Stack.top(); Stack.pop();
					bccno[p] = bcnt; 
				} while(p != {u, v});	
			}
			if(!fa && chd > 1) 
				ansv.insert(u);
			if(fa && low[v] >= dfn[u])
				ansv.insert(u);
		}
		else if(v != fa){
			low[u] = min(low[u], dfn[v]);
			Stack.push({u, v});
		}
	}
}