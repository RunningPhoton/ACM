struct Point {
	ll x, y;
	void read() {
		scanf("%lld%lld", &x, &y);
	}
	Point(ll _x = 0, ll _y = 0) : x(_x), y(_y) {}
	Point operator- (const Point& rhs) {
		return Point(x - rhs.x, y - rhs.y);
	}
	Point operator+ (const Point& rhs) {
		return Point(x + rhs.x, y + rhs.y);
	}
	ll operator* (const Point& rhs) {
		return x * rhs.x + y * rhs.y;
	}
	ll operator^ (const Point& rhs) {
		return x * rhs.y - y * rhs.x;
	}
	bool operator< (const Point& rhs) const {
		if(x == rhs.x) return y < rhs.y;
		return x < rhs.x;
	}
}p[maxv], ploy[maxv];
typedef Point Vector;
// 凸包
int Gh(Point *p, int tot) {
	sort(p, p + tot);
	int n = 0;
	for(int i = 0; i < tot; i++) {
		while(n > 1 && ((ploy[n-1] - ploy[n-2]) ^ (p[i] - ploy[n-1])) >= 0) n--;
		ploy[n++] = p[i];
	}
	int m = n;
	for(int i = tot - 2; ~i; i--) {
		while(m > n && ((ploy[m-1] - ploy[m-2]) ^ (p[i] - ploy[m-1])) >= 0) m--;
		ploy[m++] = p[i];
	}
	return m - 1;
}
// 三角形，旋转卡壳
ll getMost(Point* ploy, int n) {
	ploy[n] = ploy[0];
	int opa = 1;
	ll ans = 0;
	for(int i = 0; i < n; i++) {
		while(((ploy[opa] - ploy[i]) ^ (ploy[i+1] - ploy[i])) 
			< ((ploy[(opa+1)%n] - ploy[i]) ^ (ploy[i+1] - ploy[i]))) 
			opa = (opa + 1) % n;
		ans = max(ans, (ploy[opa] - ploy[i]).dis2());
		// printf("%d  %d\n", i, opa);
	}
	return ans;
}