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
void Conv(Virt a[], Virt b[], int len) {
	FFT(a, len, 1);
	FFT(b, len, 1);
	for(int i = 0; i < len; i++)
		a[i] = a[i] * b[i];
	FFT(a, len, -1);
}

int result[maxn];
int len;
Virt va[maxn], vb[maxn];

void work() {
	Conv(va, vb, len);
	for(int i = 0; i < len; i++) {
		result[i] = va[i].r + 0.5;
	}
}