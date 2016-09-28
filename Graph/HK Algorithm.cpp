struct Edge{
	int to, next;	
}edge[maxm];

int ecnt, head[maxn], dis, nx, ny;
int xlink[maxn], ylink[maxn], dx[maxn], dy[maxn], vs[maxn];
int ax[maxn], bx[maxn], ay[maxn], by[maxn], vis[maxn];


void init() {
	ecnt = 0;
	memset(head, -1, sizeof head);
	memset(xlink, -1, sizeof xlink);
	memset(ylink, -1, sizeof ylink);
}

void add_edge(int u, int v) {
	edge[ecnt].to = v;	
	edge[ecnt].next = head[u];	
	head[u] = ecnt++;
}

bool BFS() {
	queue<int> que;	dis = inf;
	memset(dx, -1, sizeof dx);
	memset(dy, -1, sizeof dy);
	for(int i = 1; i <= nx; i++) {
		if(xlink[i] == -1) {
			que.push(i);
			dx[i] = 0;
		}
	}
	while(que.size()) {
		int u = que.front(); que.pop();
		if(dx[u] > dis) break;
		for(int i = head[u]; ~i; i = edge[i].next) {
			int v = edge[i].to;	
			if(dy[v] == -1) {
				dy[v] = dx[u] + 1;
				// find augmenting-path				
				if(ylink[v] == -1) dis = dy[v];
				else {
					dx[ylink[v]] = dy[v] + 1;
					que.push(ylink[v]);
				}
			}
		}
	}
	return dis != inf;
}

bool DFS(int u) {
	for(int i = head[u]; ~i; i = edge[i].next) {
		int v = edge[i].to;	
		// multiple augmented
		if(!vis[v] && dy[v] == dx[u] + 1) {
			vis[v] = 1;
			if(ylink[v] != -1 && dy[v] == dis) continue;	
			if(ylink[v] == -1 || DFS(ylink[v])) {
				xlink[u] = v, ylink[v] = u;
				return true;
			}
		}
	}
	return false;
}

int Hopcroft_Karp() {
	int res = 0;	
	while(BFS()) {
		memset(vis, 0, sizeof vis);
		for(int i = 1; i <= nx; i++)
			if(xlink[i] == -1) res += DFS(i);	
	}
	return res;
}

