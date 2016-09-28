//
//  Created by Matrix on 2015-10-29
//  Copyright (c) 2015 Matrix. All rights reserved.
//
//
//#pragma comment(linker, "/STACK:102400000,102400000")
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <sstream>
#include <set>
#include <vector>
#include <stack>
#define ALL(x) x.begin(), x.end()
#define INS(x) inserter(x, x,begin())
#define ll long long
#define CLR(x) memset(x, 0, sizeof x)
#define MAXN 9999
#define MAXSIZE 10
#define DLEN 4
using namespace std;
const int inf = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
const int maxn = 1e4 + 10;
const int maxv = 1e3 + 10;
const double eps = 1e-9;


// 最小树形图
int in[maxv], pre[maxv];
int id[maxv], vis[maxv];
struct Node {
	int u, v, cost;
}node[maxn];
int drected_mst(int root, int n, int m) {
	int ret = 0;
	while(1) {
		for(int i = 0; i < n; i++) in[i] = inf;
		for(int i = 0; i < m; i++) {
			int u = node[i].u;
			int v = node[i].v;
			if(node[i].cost < in[v] && u != v) {
				pre[v] = u;
				in[v] = node[i].cost;
			}
		}
		for(int i = 0; i < n; i++) {
			if(i == root) continue;
			if(in[i] == inf) return -1;
		}
		int cntnode = 0;
		memset(id, -1, sizeof id);
		memset(vis, -1, sizeof vis);
		in[root] = 0;
		for(int i = 0; i < n; i++) {
			ret += in[i];
			int v = i;
			while(id[v] == -1 && vis[v] != i && v != root) {
				vis[v] = i;
				v = pre[v];
			}
			if(v != root && id[v] == -1) {
				for(int u = pre[v]; u != v; u = pre[u]) {
					id[u] = cntnode;
				}
				id[v] = cntnode++;
			}
		}
		if(cntnode == 0) break;
		for(int i = 0; i < n; i++) {
			if(id[i] == -1)
				id[i] = cntnode++;
		}
		for(int i = 0; i < m; i++) {
			int v = node[i].v;
			node[i].u = id[node[i].u];
			node[i].v = id[node[i].v];
			if(node[i].u != node[i].v)
				node[i].cost -= in[v];
		}
		n = cntnode;
		root = id[root];
	}
	return ret;
}
int main() {
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt","w",stdout);
#endif


	return 0;
}

