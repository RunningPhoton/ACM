#include <cstdio>
#include <iostream>
using namespace std;

class SplayTree {
public:
	struct Node {
		int sz, val;
		Node *pre, *ch[2];
		Node(int b = 0){ sz = b; }
		void rs() { sz = ch[0]->sz + ch[1]->sz + 1; }
	}*null, *root, pool[maxn];
	
	int psz; stack<Node*> freelist;
	SplayTree() { clear(); }
			
	void clear() {
		null = new Node;
		null->pre = null->ch[0] = null->ch[1] = null;
		root = null; psz = 0;
		while(freelist.size()) freelist.pop();
	}
	
	Node* NewNode(int v) {
		Node *p;
		if(freelist.size()) {
			p = freelist.top();	
			freelist.pop();
		}
		else p = &pool[psz++]; 
		p->sz = 1; p->val = v;
		p->ch[0] = p->ch[1] = p->pre = null;
		return p;
	}
	
	void pushUp(Node *x) { x->rs(); }
	void pushDownsh(Node *x) { return; }

	void rotate(Node* &x, int k) {
		Node *y = x->pre;
		pushDown(y), pushDown(x);
		y->ch[!k] = x->ch[k];
		if(x->ch[k] != null) x->ch[k]->pre = y;
		x->pre = y->pre;
		if(y->pre != null)
			if(y->pre->ch[0] == y) y->pre->ch[0] = x;
			else y->pre->ch[1] = x;
		x->ch[k] = y, y->pre = x;
		if(y == root) root = x; pushUp(y);
	}
			 
	void splay(Node* x, Node* target) {
		pushDown(x);
		while(x->pre != target) {
			Node *y = x->pre;
			int d = x != y->ch[0];
			if(y->pre != target && y == y->pre->ch[d]) 
				rotate(y, d ^ 1);
			rotate(x, d ^ 1);
		}
		if(target == null) root = x; pushUp(x);
	}
	
    void select(int k, Node* x, Node* target) {
        while(true) {
			pushDown(x);       
		    if(k == x->ch[0]->sz + 1) break;
			if (k <= x->ch[0]->sz)
                x = x->ch[0];
            else {
                k -= x->ch[0]->sz + 1;
            	x = x->ch[1];
        	}
        }
        splay(x, target);
    }
				
	void build(Node* &x, int l, int r, int *a, Node* &fa) {
		if(r < l) return;
		int mid = l + r >> 1;
		x = NewNode(a[mid]); x->pre = fa;
		build(x->ch[0], l, mid - 1, a, x);
		build(x->ch[1], mid + 1, r, a, x);
		pushUp(x);
	}
		
	void recover(Node* x) {
		if(x == null) return;
		freelist.push(x);
		recover(x->ch[0]);
		recover(x->ch[1]);
	}	

} spy;
