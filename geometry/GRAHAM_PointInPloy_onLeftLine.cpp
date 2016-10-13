int Gh(Point *p, int tot) {
	sort(p, p + tot);
	int n = 0;
	for(int i = 0; i < tot; i++) {
		while(n > 1 && ((ploy[n-1] - ploy[n-2]) ^ (p[i] - ploy[n-1])) <= 0) n--;
		ploy[n++] = p[i];
	}
	int m = n;
	for(int i = tot - 2; ~i; i--) {
		while(m > n && ((ploy[m-1] - ploy[m-2]) ^ (p[i] - ploy[m-1])) <= 0) m--;
		ploy[m++] = p[i];
	}
	return m - 1;
}
bool onSegment(Point a, Point b, Point p) {
	return comp((a-p)*(b-p)) <= 0 && comp((a-p)^(b-p)) == 0;
}
int isPointInPolygon(Point p, vector <Point>& poly) {
    int wn = 0;
    int n = poly.size();
    for(int i = 0; i < n; i++) {
        if(onSegment(poly[i], poly[(i+1)%n], p)) return -1; //在边界上
        int k = comp(((poly[(i+1)%n] - poly[i]) ^ (p - poly[i])));
        int d1 = comp(poly[i].y - p.y);
        int d2 = comp(poly[(i+1)%n].y - p.y);
        if(k > 0 && d1 <= 0 && d2 > 0) wn++;
        if(k < 0 && d2 <= 0 && d1 > 0) wn--;
    }
    if(wn != 0) return 1; //在内部
    return 0; //在外部
}
bool PolyOnLeft(Point p, Point q, vector <Point>& poly) {
	Vector v = q - p;
	for(int i = 0; i < poly.size(); i++) {
		if(comp(v ^ (poly[i] - p)) < 0) return false;
	}
	return true;
}
