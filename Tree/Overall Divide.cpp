struct Node {
	int id, x, y, k;	
	Node() {}
	Node(int _id, int _x, int _y, int _k) : id(_id), x(_x), y(_y), k(_k) {}
}q[maxn], q1[maxn], q2[maxn];

int n, a[maxn], b[maxn], c[maxn], ans[maxn];

void divide(int head, int tail, int l, int r) {
	if(l == r) {
		for(int i = head; i <= tail; i++)
			if(q[i].id) ans[q[i].id] = b[l];
		return;
	} 
	int m = l + r >> 1, c1 = 0, c2 = 0;
	for(int i = head; i <= tail; i++) {
		if(!q[i].id) {
			if(q[i].k <= m) {
				add(q[i].x, q[i].y);
				q1[c1++] = q[i];
			} else q2[c2++] = q[i];
		} else {
			int num = sum(q[i].y) - sum(q[i].x - 1);	
			if(q[i].k <= num)
				q1[c1++] = q[i];
			else {
				q[i].k -= num;
				q2[c2++] = q[i];
			}
		}
	}
	for(int i = 0; i < c1; i++)
		if(!q1[i].id) add(q1[i].x, -q1[i].y);
	memcpy(q + head +  0, q1, sizeof(Node) * c1);
	memcpy(q + head + c1, q2, sizeof(Node) * c2);
	divide(head, head + c1 - 1, l, m);
	divide(head + c1, tail, m + 1, r);
}

int main() {
	int Q, tot, num, cnt;
	while(~scanf("%d", &n)) {
		num = tot = 0;
		for(int i = 1; i <= n; i++) {
			scanf("%d", a + i);b[i] = a[i];
			q[++tot] = Node(0, i, 1, a[i]);
		} 
		scanf("%d", &Q); cnt = n;
		for(int i = 1; i <= Q; i++) {
			int ope, x, y, k;
			scanf("%d %d %d", &ope, &x, &y);
			if(ope == 1) {
				q[++tot] = Node(0, x, -1, a[x]);
				q[++tot] = Node(0, x,  1,    y);
				a[x] = y; b[++cnt] = y;
			} else {
				scanf("%d", &k);
				q[++tot] = Node(++num, x, y, k);
			}
		}
		sort(b + 1, b + 1 + cnt);
		int m = unique(b + 1, b + 1 + cnt) - b - 1;
		for(int i = 1; i <= tot; i++) {
			if(q[i].id) continue;
			q[i].k = lower_bound(b + 1, b + 1 + m, q[i].k) - b;
		}
		divide(1, tot, 1, m);
		for(int i = 1; i <= num; i++)
			printf("%d\n", ans[i]);
	}
	return 0;
}
