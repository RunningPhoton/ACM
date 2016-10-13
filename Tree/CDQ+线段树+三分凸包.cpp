#include <bits/stdc++.h>
using namespace std;
#define lson l, mid, rt << 1
#define rson mid + 1, r, rt << 1 | 1
typedef long long LL;
const LL INF = 0x3f3f3f3f3f3f3f3f;
const int maxn = 50005;
struct Point{
    LL x, y;
    Point(){}
    Point(LL _x, LL _y): x(_x), y(_y) {}

    Point operator-(const Point& tmp) const{
        return Point(x - tmp.x, y - tmp.y);
    }

    LL dot(const Point& tmp) const{
        return x * tmp.x + y * tmp.y;
    }

    LL det(const Point& tmp) const{
        return x * tmp.y - y * tmp.x;
    }

    bool operator<(const Point& tmp) const{
         return x < tmp.x || x == tmp.x && y < tmp.y;
    }

}query[maxn], S[maxn];
int ope[maxn], del[maxn];
LL ans[maxn];
vector < Point > p[maxn << 2];
int n, top;
map<pair<int, int>, int> mp;

void add(int L, int R, int x, int l = 1, int r = n, int rt = 1){
    if(L <= l && r <= R){
        p[rt].push_back(query[x]);
        return;
    }
    int mid = (l + r) >> 1;
    if(L <= mid) add(L, R, x, lson);
    if(mid  < R) add(L, R, x, rson);
}

void cal(int x){
    int l = 1, r = top, mid1, mid2;
    while(r - l >= 3) { // third sreach
        mid1 = (l * 2 + r) / 3;
        mid2 = (l + r * 2) / 3;
        if(query[x].dot(S[mid1]) < query[x].dot(S[mid2]))
            l = mid1;
        else
            r = mid2;
    }
    for(int i = l; i <= r; i++)
        ans[x] = max(ans[x], query[x].dot(S[i]));
}

void solve(int l = 1, int r = n, int rt = 1){
    if(l != r){
        int mid = (l + r) >> 1;
        solve(lson);
        solve(rson);
    }
    sort(p[rt].begin(), p[rt].end());
    top = 0;
    for(int i = 0; i < p[rt].size(); i++) { // increase line
        while(top > 1 && (S[top] - S[top - 1]).det(p[rt][i] - S[top - 1]) >= 0) top--;
        S[++top] = p[rt][i];
    }
    if(top)
        for(int i = l; i <= r; i++) {
            if(!ope[i]) cal(i);
    }
    top = 0;
    for(int i = 0; i < p[rt].size(); i++) {
        while(top > 1 && (S[top] - S[top - 1]).det(p[rt][i] - S[top - 1]) <= 0) top--;
        S[++top] = p[rt][i];
    }
    if(top) {
        for(int i = l; i <= r; i++){
            if(!ope[i]) cal(i);
        }
    }
}

int main(){
    LL x, y;
    while(scanf("%d", &n) && n){
        for(int i = 0; i < maxn * 4; i++) p[i].clear();
        fill(ans, ans + n + 1, -INF);
        fill(del, del + n + 1, 0);
        mp.clear();
        for(int i = 1; i <= n; i++){
            scanf("%d", &ope[i]);
            if(ope[i] == 1) { // insert
                scanf("%lld %lld", &query[i].x, &query[i].y);
                mp[make_pair(query[i].x, query[i].y)] = i;
            }else if(ope[i] == -1) { // delete
                scanf("%lld %lld", &x, &y);
                int idx = mp[make_pair(x, y)];
                del[idx] = 1;
                add(idx, i, idx); // alive time
            } else // query
                scanf("%lld%lld", &query[i].x, &query[i].y);
        }
        for(int i = 1; i <= n; i++) { 
            if(ope[i] == 1 && !del[i])
                add(i, n, i);
        }
        solve();
        for(int i = 1; i <= n; i++){
            if(!ope[i]){
                if(ans[i] == -INF) ans[i] = 0;
                printf("%lld\n", ans[i]);
            }
        }
    }
    return 0;
}