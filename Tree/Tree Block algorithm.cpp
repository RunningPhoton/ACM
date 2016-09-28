#include <map>
#include <set>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 15;
const int maxm = 1e6 + 15;

struct Edge {
 	int to, next;
} edge[maxm];

int head[maxm], ecnt, bhead[maxn], bcnt, bsize;
int w[maxn], belong[maxn], par[maxn];

void add(int* _head, int u, int v) {
	edge[ecnt].to = v;
	edge[ecnt].next = _head[u];
	_head[u] = ecnt++;
}

struct Block {
	int data[210], sz;
	Block() { sz = 0; }
	void insert(int x) {
		int i; sz++;
		for(i = sz; i > 1 and data[i - 1] > x; i--)
			data[i] = data[i - 1]; data[i] = x;
	}
	void modify(int x, int y) {
		int pos = lower_bound(data + 1, data + 1 + sz, x) - data; data[pos] = y; 
		while(pos < sz and data[pos] > data[pos + 1]) 
			swap(data[pos], data[pos + 1]), pos++; 
		while(pos > 1  and data[pos] < data[pos - 1]) 
			swap(data[pos], data[pos - 1]), pos--;
	}
	int query(int x) {
		int res = upper_bound(data + 1, data + 1 + sz, x) - data - 1;
		return sz - res; 
	}
} block[maxn >> 1];

void dfs(int u, int fa) {
	par[u] = fa;
	if(block[belong[fa]].sz == bsize) {
		block[belong[u] = ++bcnt].insert(w[u]);
		add(bhead, belong[fa], bcnt);
	} else {
		belong[u] = belong[fa];
		block[belong[u]].insert(w[u]);
	}
	for(int i = head[u]; ~i; i = edge[i].next) {
		int v = edge[i].to;
		if(v != fa) dfs(v, u);
	}
}

int dfs_block(int u, int val) {
	int res = block[u].query(val);
	for(int i = bhead[u]; ~i; i = edge[i].next) {
		int v = edge[i].to;
		res += dfs_block(v, val);
	}
	return res;
}

int dfs(int u, int fa, int val) {
	int res = 0;
	if(w[u] > val) res++;
	for(int i = head[u]; ~i; i = edge[i].next) {
		int v = edge[i].to;
		if(v == fa) continue;
		if(belong[v] != belong[u])
			res += dfs_block(belong[v], val);		
		else res += dfs(v, u, val);
	}
	return res;
}

int main() {
#ifdef NEKO
	freopen("in.txt", "r", stdin);
#endif
	int n; scanf("%d", &n);
	bcnt = ecnt = 0; 
	memset( head, -1, sizeof  head);
	memset(bhead, -1, sizeof bhead);
	for(int i = 1; i < n; i++) {
		int u, v; scanf("%d %d", &u, &v);
		add(head, u, v);
		add(head, v, u);
	}
	belong[0] = ++bcnt;
	bsize = (int)sqrt(n + 0.5); 
	for(int i = 1; i <= n; i++) 
		scanf("%d", w + i);
	dfs(1, 0); int m, last = 0; scanf("%d", &m);
	while(m--) {
		int ope, u, x;
		scanf("%d %d %d", &ope, &u, &x);
		u ^= last, x ^= last;
		if(ope == 0)
			printf("%d\n", last = dfs(u, par[u], x));
		if(ope == 1)
			block[belong[u]].modify(w[u], x), w[u] = x;
		if(ope == 2) {
			add(head, u, ++n); w[n] = x;
			if(block[belong[u]].sz == bsize) {
				block[belong[n] = ++bcnt].insert(x);
				add(bhead, belong[u], bcnt);
			}
			else block[belong[n] = belong[u]].insert(x);
		}
	}
	return 0;
}