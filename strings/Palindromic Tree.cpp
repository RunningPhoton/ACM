
struct Palindromic_Tree {
    int next[maxn][max_index];//next指针，next指针和字典树类似，指向的串为当前串两端加上同一个字符构成
    int fail[maxn];//fail指针，失配后跳转到fail指针指向的节点
    int cnt[maxn];
    int num[maxn];
    int len[maxn];//len[i]表示节点i表示的回文串的长度
    int S[maxn];//存放添加的字符
    int last;//指向上一个字符所在的节点，方便下一次add
    int n;//字符数组指针
    int p;//节点指针
    int newnode(int l) {//新建节点
        memset(nxt[p], 0x00, sizeof nxt[p]);
        cnt[p] = 0;
        num[p] = 0;
        len[p] = l;
        return p++;
    }
    void init() {//初始化
        p = 0;
        newnode(-1);
        newnode(0);
        last = 0;
        n = 0;
        S[n] = -1;//开头放一个字符集中没有的字符，减少特判
    }
    int get_fail(int x) {//和KMP一样，失配后找一个尽量最长的
        while (S[n - len[x] - 1] != S[n]) x = fail[x];
        return x;
    }
    void add(char c) {
        c -= 'a';
        S[++n] = c;
        int cur = get_fail(last);//通过上一个回文串找这个回文串的匹配位置
        if (!next[cur][c]) {//如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
            int now = newnode(len[cur] + 2);//新建节点
            fail[now] = next[get_fail(fail[cur])][c];//和AC自动机一样建立fail指针，以便失配后跳转
            next[cur][c] = now;
            num[now] = num[fail[now]] + 1;
        }
        last = next[cur][c];
        cnt[last]++;
    }
    void count() {
        for (int i = p - 1; ~i; i--) cnt[fail[i]] += cnt[i];
        //父亲累加儿子的cnt，因为如果fail[v]=u，则u一定是v的子回文串！
    }
};
