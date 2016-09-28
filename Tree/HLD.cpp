class HLD {
public:
	int par[maxn], son[maxn], size[maxn];
	int top[maxn], dep[maxn], tid[maxn], tot;
	void init() {
		tot = 0; memset(tid, 0, sizeof tid);
	}
	void dfs1(int u, int fa, int depth = 0) {
		par[u] = fa; dep[u] = depth;
		size[u] = 1; son[u] = 0; 
		int maxx = 0;
		for(int i = g.head[u]; ~i; i = g.edge[i].next) {
			int v = g.edge[i].to, cost = g.edge[i].cost;
			if(v == fa) continue;
			dfs1(v, u, depth + 1);
			size[u] += size[v];
			if(size[v] > maxx) {
				maxx = size[v];
				son[u] = v;
			}
		}
		return;
	}

	void dfs2(int u, int acs) {
		tid[u] = ++tot, top[u] = acs;
		if(!son[u]) return;
		dfs2(son[u], acs);
		for(int i = g.head[u]; ~i; i = g.edge[i].next) {
			int v = g.edge[i].to;
			if(tid[v]) continue;
			dfs2(v, v);
		}
	}

	int pathLength(int u, int v) {
		int f1 = top[u], f2 = top[v], res = 0;
		while(f1 != f2) {
			if(dep[f1] < dep[f2]) 
				swap(f1, f2), swap(u, v);
			res += query(tid[f1], tid[u]);
			u = par[f1], f1 = top[u];
		}
		if(u == v) return res;
		if(dep[u] > dep[v]) swap(u, v);
		return res += query(tid[son[u]], tid[v]);
	}
}hld;