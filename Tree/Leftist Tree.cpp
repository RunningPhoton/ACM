struct tree {
    int l, r, v, dis, f;
} heap[maxn];

int merge(int a, int b) {
    if(!a) return b;
    if(!b) return a;
    if(heap[a].v < heap[b].v) swap(a, b); // < : max heap > : min heap  
    heap[a].r = merge(heap[a].r, b);0
    heap[heap[a].r].f = a;
    if(heap[heap[a].l].dis < heap[heap[a].r].dis) swap(heap[a].l, heap[a].r);
    if(!heap[a].r) heap[a].dis = 0;
    else heap[a].dis = heap[heap[a].r].dis + 1;
    return a;
}
 
int pop(int a) {
    int l = heap[a].l;
    int r = heap[a].r;
    heap[l].f = l;
    heap[r].f = r;
    heap[a].l = heap[a].r = heap[a].dis = 0;
    return merge(l, r);
}

int find(int a) { return heap[a].f == a ? a : find(heap[a].f); }