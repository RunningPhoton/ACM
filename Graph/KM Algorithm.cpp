int lx[maxn], ly[maxn], n;
bool sx[maxn], sy[maxn];
int match[maxn], val[maxn][maxn];

bool DFS(int u) {
	sx[u] = true;
	for(int v = 1; v <= n; v++)
		if(!sy[v] && lx[u] + ly[v] == val[u][v]) {
			sy[v] = true;
			if(match[v] == -1 || DFS(match[v])) {
				match[v] = u;
				return true;
			}
		}
	return false;
}
int Kuhn_Munkres() {
	for(int i = 1; i <= n; i++) {
		lx[i] = -inf; ly[i] = 0;
		for(int j = 1; j <= n; j++)
			if(lx[i] < val[i][j])
				lx[i] = val[i][j];
	}
	memset(match, -1, sizeof match);
	for(int u = 1; u <= n; u++)
		while(1) {
			memset(sx, 0, sizeof sx);
			memset(sy, 0, sizeof sy);
			if(DFS(u)) break;

			int dx = inf;
			for (int i = 1; i <= n; i++)
				if(sx[i])
					for(int j = 1; j <= n; j++)
						if(!sy[j])
							dx = min(lx[i] + ly[j] - val[i][j], dx);
			for (int i = 1; i <= n; i++) {
				if(sx[i]) lx[i] -= dx;
				if(sy[i]) ly[i] += dx;
			}
		}
	int sum = 0;
	for (int i = 1; i <= n; i++)
		sum += val[match[i]][i];
	return sum;
}