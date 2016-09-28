ll c[2][2][maxn][maxn];
ll mon[55];

inline lowbit(int x) { return x & -x; }

ll query(int x, int y) {
	ll res = 0;
	for(int i = x; i; i -= lowbit(i))
	for(int j = y; j; j -= lowbit(j))
		res ^= c[x & 1][y & 1][i][j];
	return res;
}

void update(int x, int y, ll v) {
	for(int i = x; i < maxn; i += lowbit(i))
	for(int j = y; j < maxn; j += lowbit(j))
		c[x & 1][y & 1][i][j] ^= v;
}

int main() {
	int x, y, xx, yy;
	if(ope[0] == 'Q') {
		x--, y--;
		ll ans = query(x, y) ^ query(x, yy) ^ query(xx, y) ^ query(xx, yy);
	} else {
		ll o;
		xx++, yy++;
		update( x,  y, o);
		update( x, yy, o);
		update(xx,  y, o);
		update(xx, yy, o);
	}
	return 0;
}