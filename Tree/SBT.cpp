
class SBT {
public:
	struct Node {
		int sz, key;
		Node *ch[2];
		void rs() { sz = ch[0]->sz + ch[1]->sz + 1; } 
	}pool[maxn], *null, *root;
	int psz; 

	SBT() { clear(); }

	void down(Node *x) {}

	Node* newNode(int key) {
		Node *p = &pool[psz++];
		p->ch[0] = p->ch[1] = null;
		p->sz = 1; p->key = key;
		return p;
	}

	void clear() {
		null = &pool[0], psz = 1, null->sz = 0;
		null->ch[0] = null->ch[1] = null; root = null;
	}

	void rotate(Node* &x, int k) {
		Node *y = x->ch[k ^ 1];
		down(x), down(y);
		x->ch[k ^ 1] = y->ch[k];
		y->ch[k] = x;
		y->sz = x->sz;
		x->rs(); x = y;
	}

	void maintain(Node* &x, int k) {
		down(x);
		if(x->ch[k]->ch[k]->sz > x->ch[k ^ 1]->sz)
			rotate(x, k ^ 1);
		else if(x->ch[k ^ 1]->ch[k]->sz > x->ch[k ^ 1]->sz) {
			rotate(x->ch[k], k);
			rotate(x, k ^ 1);
		}
		else return;
		maintain(x->ch[0], 0);
		maintain(x->ch[1], 1);
		maintain(x, 0);
		maintain(x, 1);
	}

	Node* search(int k) {
		Node *x = root;
		while(true) {
			if(x == null or k == x->key) return x; 
			int d = k >= x->key;
			x = x->ch[d];
		}
		return null;
	}

	void insert(Node* &x, int key) {
		int d = key >= x->key;
		if(x == null)
			x = newNode(key);
		else {
			x->sz++;
			insert(x->ch[d], key);
		}
		maintain(x, d);
	}

	void del(Node* &x, int key) {
		x->sz--; 
		if(key > x->key)
			del(x->ch[1], key);
		else if(key < x->key)
			del(x->ch[0], key);
		else {
			if(x->ch[0] == null or x->ch[1] == null)
				x = x->ch[0] == null ? x->ch[1] : x->ch[0];
			else {
				Node *y = x->ch[1];
				while(y->ch[0] != null) y = y->ch[0];
				x->key = y->key;
				del(x->ch[1], y->key);
			}
		}
	}

	Node* succ(Node *x, Node* y, int key) {
		if(x == null) return y;
		if(x->key >= key)
			return succ(x->ch[0], x, key);
		return succ(x->ch[1], y, key);
	}

	Node* prec(Node *x, Node* y, int key) {
		if(x == null) return y;
		if(x->key > key)
			return prec(x->ch[0], y, key);
		else 
			return prec(x->ch[1], x, key);
	}

	Node* select(Node* x, int k) {
		down(x);
		int tmp = x->ch[0]->sz + 1;
		if(tmp == k) return x;
		if(tmp > k)
			return select(x->ch[0], k);
		return select(x->ch[1], k - tmp);
	}

}sbt;