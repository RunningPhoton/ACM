struct DLX {
	int n, m, size;
	int U[maxn], D[maxn], R[maxn], L[maxn], Row[maxn], Col[maxn];
	int H[1005], S[1005];
	int ans;
	
	void init(int _n,int _m) {
		n = _n, m = _m, ans = inf;
		for(int i = 0; i <= m; i++) {
			S[i] = 0;
			U[i] = D[i] = i;
			L[i] = i - 1;
			R[i] = i + 1;
		}
		R[m] = 0, L[0] = size = m;
		for(int i = 1; i <= n; i++)
			H[i] = -1;
	}
	
	void Link(int r, int c) {
		++S[Col[++size] = c];
		Row[size] = r;
		D[size] = D[c]; // 
		U[D[c]] = size;
		U[size] = c;
		D[c] = size;
		if(H[r] < 0) H[r] = L[size] = R[size] = size;
		else {
			R[size] = R[H[r]];
			L[R[H[r]]] = size;
			L[size] = H[r];
			R[H[r]] = size;
		}
	}

//  exact cover
	void remove(int c) {
		L[R[c]] = L[c];
		R[L[c]] = R[c];
		for(int i = D[c]; i != c; i = D[i])
			for(int j = R[i]; j != i; j = R[j]) {
				U[D[j]] = U[j];
				D[U[j]] = D[j];
				--S[Col[j]];
			}
	}
	
	void resume(int c) {
		for(int i = U[c]; i != c; i = U[i])
			for(int j = L[i]; j != i; j = L[j])
				++S[Col[U[D[j]] = D[U[j]] = j]];
		L[R[c]] = R[L[c]] = c;
	}

	void Dance(int d) {
		if(d >= ans && ans != inf) return;
		if(!R[0]) { ans = min(ans, d); return; }
		int c = R[0];
		for(int i = R[0]; i != 0; i = R[i])
			if(S[i] < S[c])
				c = i;
		remove(c);
		for(int i = D[c]; i != c; i = D[i]) {
			for(int j = R[i]; j != i; j = R[j]) remove(Col[j]);
			Dance(d + 1);
			for(int j = L[i]; j != i; j = L[j]) resume(Col[j]);
		}
		resume(c);
		return;
	}
// end of exact	cover
	
// multi cover	

	void del(int c) {
		for(int i = D[c]; i != c; i = D[i])
			L[R[i]] = L[i], R[L[i]] = R[i];
	}
	
	void rec(int c) {
		for(int i = U[c]; i != c; i = U[i])
			L[R[i]] = R[L[i]] = i;
	}
	
	bool v[maxn];
	int h() {
		int res = 0;
		for(int c = R[0]; c; c = R[c]) v[c] = true;
		for(int c = R[0]; c; c = R[c]) {
			if(!v[c]) continue;	
			res++; v[c] = false;
			for(int i = D[c]; i != c; i = D[i])
				for(int j = R[i]; j != i; j = R[j])			
					v[Col[j]] = false;	
		}
		return res;
	}
	
	void dance(int d) {
		if(d + h() >= ans) return;
		if(!R[0]) { ans = min(ans, d); return; }
		int c = R[0];
		for(int i = R[0]; i; i = R[i])
			if(S[i] < S[c]) c = i;
		
		for(int i = D[c]; i != c; i = D[i]) {
			del(i);	
			for(int j = R[i]; j != i; j = R[j]) del(j);
			dance(d + 1);
			for(int j = L[i]; j != i; j = L[j]) rec(j);
			rec(i);
		}
		return;
	}
// end of multi cover	
	
} dlx;