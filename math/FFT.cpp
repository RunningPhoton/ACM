struct Virt {
	double r, i;
	Virt(double _r = 0, double _i = 0) : r(_r), i(_i) {}
	Virt operator+ (Virt& rhs) {
		return Virt(r + rhs.r, i + rhs.i);
	}
	Virt operator- (Virt& rhs) {
		return Virt(r - rhs.r, i - rhs.i);
	}
	Virt operator* (Virt& rhs) {
		return Virt(r * rhs.r - i * rhs.i, r * rhs.i + i * rhs.r);
	}
};
void Rader(Virt F[], int len) {
	int j = len >> 1;
	for(int i = 1; i < len - 1; i++) {
		if(i < j) swap(F[i], F[j]);
		int k = len >> 1;
		while(j >= k) {
			j -= k;
			k >>= 1;
		}
		if(j < k) j += k;
	}
}
void FFT(Virt F[], int len, int on) {
	Rader(F, len);
	for(int h = 2; h <= len; h <<= 1) { 
		Virt wn(cos(-on*2*PI/h), sin(-on*2*PI/h)); 
		for(int j = 0; j < len; j += h) {
			Virt w(1, 0);
			for(int k = j; k < j + h / 2; k++) {
				Virt u = F[k];
				Virt t = w * F[k + h / 2];
				F[k] = u + t;	
				F[k + h / 2] = u - t;
				w = w * wn;
			}
		}
	}
	if(on == -1)
		for(int i = 0; i < len; i++)
			F[i].r /= len;
}
// 黑科技，FFT取膜 cov(p, q)
void Cov(int p[], int q[], int m) {
	int t = sqrt(MOD), len = 1;
	while(len < 2 * m) len <<= 1;
	for(int i = 0; i < len; i++) {
		p1[i] = (i < m ? p[i] / t : 0);
		p2[i] = (i < m ? p[i] % t : 0);
		p3[i] = 0;
		q1[i] = (i < m ? q[i] / t : 0);
		q2[i] = (i < m ? q[i] % t : 0);
	}
	FFT(p1, len, 1), FFT(p2, len, 1), FFT(q1, len, 1), FFT(q2, len, 1);
	for(int i = 0; i < len; i++) {
		p3[i] = p1[i] * q2[i] + p2[i] * q1[i];
		p1[i] = p1[i] * q1[i];
		p2[i] = p2[i] * q2[i];
	}
	FFT(p1, len, -1), FFT(p2, len, -1), FFT(p3, len, -1);
	for(int i = 0; i < len; i++) {
		ll t1 = p1[i].r + 0.5;
		ll t2 = p2[i].r + 0.5;
		ll t3 = p3[i].r + 0.5;
		p[i] = (t1 * t * t + t * t3 + t2) % MOD;
	}
	for(int i = m; i < len; i++) {
		p[i%m] = (p[i%m] + p[i]) % MOD;
		p[i] = 0;
	}
}