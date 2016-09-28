//最后点放在p[m]
int m;
inline bool zero(double a) {return abs(a) < eps;}
struct Point {
    double x, y;
    Point (double _x = 0, double _y = 0) : x(_x), y(_y) {}
    Point operator+ (Point rhs) {
        return Point(x + rhs.x, y + rhs.y);
    }
    Point operator- (Point rhs) {
        return Point(x - rhs.x, y - rhs.y);
    }
    double operator* (Point rhs) {
        return x * rhs.x + y * rhs.y;
    }
    double operator^ (Point rhs) {
        return x * rhs.y - y * rhs.x;
    }
}p[maxn*2];
struct Segment {
    Point s, e;
    double angle;
    void getAngle(){angle = atan2(e.y - s.y, e.x - s.x);}
    //偏移dis距离
    void change(double dis) {
        double len = (e - s).getDis();
        double dx = (s.y - e.y) / len * dis;
        double dy = (e.x - s.x) / len * dis;
        s = s + Point(dx, dy);
        e = e + Point(dx, dy);
    }
}seg[maxn];
Point getIntersect(Segment s1, Segment s2){
    double u = (s1.e - s1.s) ^ (s2.s - s1.s);
    double v = (s1.s - s1.e) ^ (s2.e - s1.e);
    Point t;
    t.x = (s2.s.x * v + s2.e.x * u) / (u + v); 
    t.y = (s2.s.y * v + s2.e.y * u) / (u + v);
    return t;
}
bool cmp(Segment s1, Segment s2){
    //先按极角排序
    if(s1.angle < s2.angle - eps) return true;
    //极角相等，内侧的在前
    else if(zero(s1.angle - s2.angle) && ((s2.e - s2.s) ^ (s1.e - s2.s)) > -eps) return true;
    return false;
}
Segment deq[maxn];
// 逆时针把线段加入到seg里面
void HalfPlaneIntersect(Segment seg[], int n){
    sort(seg, seg + n, cmp);
    int tmp = 1;
    for(int i = 1; i < n; ++i)
        if(!zero(seg[i].angle - seg[tmp-1].angle))
            seg[tmp++] = seg[i];
    n = tmp;
    deq[0] = seg[0]; deq[1] = seg[1];
    int head = 0, tail = 1;
    for(int i = 2; i < n; ++i){
        while(head < tail && ((seg[i].e - seg[i].s) ^ (getIntersect(deq[tail],deq[tail-1]) - seg[i].s)) < -eps) tail--;
        while(head < tail && ((seg[i].e - seg[i].s) ^ (getIntersect(deq[head],deq[head+1]) - seg[i].s)) < -eps) head++;
        deq[++tail] = seg[i];
    }
    while(head < tail && ((deq[head].e - deq[head].s) ^ (getIntersect(deq[tail],deq[tail-1]) - deq[head].s)) < -eps) tail--;
    while(head < tail && ((deq[tail].e - deq[tail].s) ^ (getIntersect(deq[head],deq[head+1]) - deq[tail].s)) < -eps) head++;
    if(head == tail) return;
    m = 0;
    for(int i = head; i < tail; ++i)
        p[m++] = getIntersect(deq[i], deq[i+1]);
    if(tail > head + 1)
        p[m++] = getIntersect(deq[head], deq[tail]);
}
double getArea(Point p[], int &n){
    double area = 0;
    for(int i = 1; i < n - 1; ++i)
        area += (p[i] - p[0]) ^ (p[i+1] - p[0]);
    return fabs(area) / 2.0;
}