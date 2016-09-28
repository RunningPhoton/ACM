int f[10][10][1005][1005];
#define ff(x,y) f[0][0][x][y]
#define gg(x,y) f[k1][k2][x][y]

namespace sparse_table_2D {
	inline int query(int x1, int y1, int x2, int y2) {
		int k1 = 31 - __builtin_clz(x2 - x1 + 1);
		int k2 = 31 - __builtin_clz(y2 - y1 + 1);
		return max(max(gg(x2, y2), gg(x1 + (1 << k1) - 1, y2)),
			   max(gg(x2, y1 + (1 << k2) - 1), gg(x1 + (1 << k1) - 1, y1 + (1 << k2) - 1)));
	}

	void init_table() {
		for(int i = 1; 1 << i <= n; i++) {
		for(int x = 1 << i; x <= n; x++)
			for(int y = 1; y <= m; y++)
				f[i][0][x][y] = max(f[i - 1][0][x][y], f[i - 1][0][x - (1 << (i - 1))][y]);
		}

		for(int i = 0; 1 << i <= n; i++) {
			for(int j = 1; 1 << j <= m; j++)
				for(int x = 1 << i; x <= n; x++)
					for(int y = 1 << j; y <= m; y++)
						f[i][j][x][y] = max(f[i][j - 1][x][y], f[i][j - 1][x][y - (1 << j - 1)]);
		}
	}	
}