struct Node {
	int val, maxx;
	Node *pre, *ch[2];
}*null, pool[maxm];

struct Edge {
	int to, cost, next, id;
}edge[maxm];

int head[maxn], ecnt, tid[maxn];

class LCT {
public:
	int psz;
	Node* rt[10005];
	LCT() { clear(); }
			
	void clear() {
		null = &pool[0]; psz = 1; null->maxx = -inf;
		null->pre = null->ch[0] = null->ch[1] = null;
	}
	
	Node* NewNode(int v = 0) {
		Node *p = &pool[psz++]; 
		p->val = p->maxx = v;
		p->ch[0] = p->ch[1] = p->pre = null;
		return p;
	}
	
	bool isroot(Node *x) {
		return x == null or (x->pre->ch[0] != x and x->pre->ch[1] != x);
	}

	void pushDown(Node *x) { 
		x->maxx = max(x->val, max(x->ch[0]->maxx, x->ch[1]->maxx)); 
	}

	void pushUp(Node *x) { 
		x->maxx = max(x->val, max(x->ch[0]->maxx, x->ch[1]->maxx)); 
	}

	void rotate(Node* &x, int k) {
		if(isroot(x)) return;
		Node *y = x->pre;
		y->ch[!k] = x->ch[k];
		if(x->ch[k] != null) x->ch[k]->pre = y;
		x->pre = y->pre;
		if(y != null)
			if(y->pre->ch[0] == y) y->pre->ch[0] = x; else 
		    if(y->pre->ch[1] == y) y->pre->ch[1] = x;
		x->ch[k] = y, y->pre = x;
		pushUp(y);
	}
		
	int tot;
	Node *sta[maxn];

	void splay(Node* x) {
		if(x == null) return;
		tot = 1; sta[0] = x;
		for(Node *y = x; !isroot(y); y = y->pre)
			sta[tot++] = y->pre;
		while(tot) pushDown(sta[--tot]);
		while(!isroot(x)) {
			Node *y = x->pre;
			int d = x != y->ch[0];
			if(!isroot(y) && y == y->pre->ch[d]) 
				rotate(y, d ^ 1);
			rotate(x, d ^ 1);
		}
		pushUp(x);
	}
	
	// just like splay
	Node *access(Node *u) {
		Node *v = null;
		while(u != null) {
			splay(u);
			if(v != null)
				v->pre = u;
			u->ch[1] = v;
			pushUp(u);
			v = u; u = u->pre;
		}
		return v;
	}

	// u merge into v
	Node *link(Node *u, Node *v) {
		access(u); splay(u);
		u->pre = v;
		return access(v);
	}

	// Node *cut(Node *u) {
	// 	access(u); splay(u);
	// 	u->ch[0] = u->ch[0]->pre = null;
	// 	pushUp(u);
	// 	return u;
	// }

	// Node *getroot(Node *u) {
	// 	access(u); splay(u);
	// 	while(u->ch[0] != null) u = u->ch[0];
	// 	splay(u);
	// 	return u;
	// }
				
	void build(int u = 1, int fa = 0) {
		if(!fa) rt[u] = NewNode(-inf);
		for(int i = head[u]; ~i; i = edge[i].next) {
			int v = edge[i].to, w = edge[i].cost;
			if(v == fa) continue;
			tid[edge[i].id] = v;
			rt[v] = NewNode(w);
			rt[v]->pre = rt[u];
			build(v, u);
		}
	}

	int ask(Node *u) {
		int res = -inf;
		Node *v = null;
		while(u != null) {
			splay(u);
			if(u->pre == null)
				res = max(u->ch[1]->maxx, v->maxx);
			v->pre = u;
			u->ch[1] = v;
			pushUp(u);
			v = u; u = u->pre;
		}
		if(res == -inf) res = 0;
		return res;
	}
			
} lct;