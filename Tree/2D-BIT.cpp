int c[maxn][maxn];

int lowbit(int x) { return x & (-x); }

void update(int X, int Y, int val) {
	int x, y;
	for(x = X ; x <= n; x += lowbit(x))
		for(y = Y ; y <= n; y += lowbit(y))
			c[x][y] += val;
}

int getsum(int X, int Y){
	int sum = 0, x, y;
	for(x = X ; x > 0; x -= lowbit(x))
		for(y = Y ; y > 0; y -= lowbit(y))
			sum += c[x][y];
	return sum;
}

int GetRec(int l, int r, int L, int R){
	int res = getsum(L, R) - getsum(l - 1, R) - getsum(L, r - 1) + getsum(l - 1, r - 1);
	return res;
}