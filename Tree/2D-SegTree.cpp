int a[805][805];

class SegmentTree2D {
public:
	int Max[maxn][maxn], Min[maxn][maxn], n, m;	
	int xo, xleaf, vmax, vmin; 
	int x1, y1, x2, y2; // query parameter
	int x, y, v;        // modify parameter
	
	void query1D(int L, int R, int o = 1) {
		if(y1 <= L && R <= y2) {
			vmax = max(Max[xo][o], vmax);
			vmin = min(Min[xo][o], vmin);	
			return;
		}
		int mid = L + R >> 1;
		if(y1 <= mid) query1D(L, mid, lson); 	
		if(y2 >  mid) query1D(mid + 1, R, rson);			
	}
	
	void query2D(int L, int R, int o = 1) {
		if(x1 <= L && R <= x2) { xo = o, query1D(1, m); return; }		
		int mid = L + R >> 1;
		if(x1 <= mid) query2D(L, mid, lson);	
		if(x2  > mid) query2D(mid + 1, R, rson);	
	}
	
	void modify1D(int L, int R, int o = 1) {
		if(L == R) {
			if(xleaf) { Max[xo][o] = Min[xo][o] = v; return; }
			Max[xo][o] = max(Max[xo * 2][o], Max[xo * 2 + 1][o]);
			Min[xo][o] = min(Min[xo * 2][o], Min[xo * 2 + 1][o]);
			return;
		} 
		int mid = L + R >> 1;
		if(y <= mid) modify1D(L, mid, lson); 	
		else modify1D(mid + 1, R, rson);
		Max[xo][o] = max(Max[xo][lson], Max[xo][rson]);
		Min[xo][o] = min(Min[xo][lson], Min[xo][rson]);	
	}
	
	void modify2D(int L, int R, int o = 1) {
		if(L == R) { xo = o, xleaf = 1, modify1D(1, m); return; }	
		int mid = L + R >> 1;
		if(x <= mid) modify2D(L, mid, lson);
		else modify2D(mid + 1, R, rson);
		xo = o, xleaf = 0; modify1D(1, m);		
	}
	
	void build1D(int L, int R, int o = 1) {
		if(L == R) {
			if(xleaf) { Max[xo][o] = Min[xo][o] = a[xleaf][L]; return; }
			Max[xo][o] = max(Max[xo * 2][o], Max[xo * 2 + 1][o]);
			Min[xo][o] = min(Min[xo * 2][o], Min[xo * 2 + 1][o]);
			return;
		}
		int mid = L + R >> 1;
		build1D(L, mid, lson);
		build1D(mid + 1, R, rson);
		Max[xo][o] = max(Max[xo][lson], Max[xo][rson]);
		Min[xo][o] = min(Min[xo][lson], Min[xo][rson]);
	}
	
	void build2D(int L, int R, int o = 1) {
		if(L == R) { xo = o, xleaf = L, build1D(1, m); return; }	
		int mid = L + R >> 1;
		build2D(L, mid, lson);
		build2D(mid + 1, R, rson);
		xo = o, xleaf = 0, build1D(1, m);	
	}
	
	void query() { vmax = -inf, vmin = inf, query2D(1, n); }
	void modify() { modify2D(1, n); }
	void build() { build2D(1, n); }
}t;