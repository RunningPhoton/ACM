struct Point {
	int x, y;
	void input() { scanf("%d %d", &x, &y); }
	int distance(const Point& rhs) {
		return abs(x - rhs.x) + abs(y - rhs.y);
	}
}point[maxm];
bool Comp_x(const Point& a, const Point& b) { return a.x < b.x; }
bool Comp_y(const Point& a, const Point& b) { return a.y < b.y; }
namespace K_Dimensional_Tree {
	struct area {
		area *ls, *rs;
		int x1, y1, x2, y2;
		Point p;
		void up(area *rhs) {
			if(!rhs) return;
			x1 = min(x1, rhs->x1);
			y1 = min(y1, rhs->y1);
			x2 = max(x2, rhs->x2);
			y2 = max(y2, rhs->y2);
		}
		int distance(const Point &p) {  
            int res = 0;  
            if(p.x < x1) res += x1 - p.x;  
            if(p.x > x2) res += p.x - x2;  
            if(p.y < y1) res += y1 - p.y;  
            if(p.y > y2) res += p.y - y2;  
            return res;  
        } 
	} pool[maxm], *root;
	int tot;
	area* newnode(const Point& p) {
		area* res = &pool[tot++];
		res->x1 = res->x2 = p.x;
		res->y1 = res->y2 = p.y;
		res->p = p;
		res->ls = res->rs = 0;
		return res;
	}
	void build(area* &x, int l, int r, int k) {
		if(l > r) return;
		int m = l + r >> 1;
		nth_element(point + l, point + m, point + r + 1, k ? Comp_x : Comp_y);
		x = newnode(point[m]);
		build(x->ls, l, m - 1, k ^ 1);
		build(x->rs, m + 1, r, k ^ 1);
		x->up(x->ls), x->up(x->rs);
	}
	void query(area* x, Point &p, int &ans) {
		ans = min(ans, p.distance(x->p));
		int l = x->ls ? x->ls->distance(p) : inf;
		int r = x->rs ? x->rs->distance(p) : inf;
		if(!x->ls and !x->rs) return;
		if(l < r) {
			if(x->ls and l < ans)
				query(x->ls, p, ans);
			if(x->rs and r < ans)
				query(x->rs, p, ans);
		} else {
			if(x->rs and r < ans)
				query(x->rs, p, ans);
			if(x->ls and l < ans)
				query(x->ls, p, ans);
		}
	}
	void insert(area* &x, const Point& p, int k = 1) {
		if(!x) { x = newnode(p); return; }
		if((k ? Comp_x : Comp_y)(p, x->p)) {
			insert(x->ls, p, k ^ 1);
			x->up(x->ls);
		} else {
			insert(x->rs, p, k ^ 1);
			x->up(x->rs);
		}
	}
};