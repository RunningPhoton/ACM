int ch[maxn][max_index];
int f[maxn], last[maxn], val[maxn];

class AC_Automation {
private:
    int sz;
public :
    AC_Automation() { sz = 1; CLR(ch[0]); }
    ~AC_Automation() {}
    int idx(char c) { return c - 'a'; }

    void Insert(char *s, int v) {
        int u = 0;
        for (int i = 0; s[i]; i++) {
            int c = idx(s[i]);
            if (!ch[u][c]) {
                CLR(ch[sz]);
                val[sz] = 0;
                ch[u][c] = sz++;
            }
            u = ch[u][c];
        }
        val[u] = v;
    }

    void get_fail(){
        f[0] = 0;
        queue<int> q;
        for (int i = 0; i < max_index; i++) {
            int u = ch[0][i];
            if (!u) continue ;
            q.push(u);
            f[u] = 0;
            last[u] = 0;
        }
        while (q.size()) {
            int r = q.front();q.pop();
            for (int i = 0; i < max_index; i++) {
                int u = ch[r][i];
                if (!u) {ch[r][i] = ch[f[r]][i];  continue;}
                q.push(u);
                int v = f[r];
                while (v && !ch[v][i]) v = f[v];
                f[u] = ch[v][i];
                last[u] = val[f[u]] ? f[u] : last[f[u]];
            }
        }
    }

    int Find(char *t){
        int j = 0, res = 0;
        for (int i = 0; t[i]; i++) {
            int c = idx(t[i]);
//            while (j && !ch[j][c]) j = f[j];
            j = ch[j][c];
            if (val[j]) print(j);
            else if (last[j]) print(last[j]);
        }
        return res;
    }

    void print(int j) {
        if (!j) return ;
        print(last[j]);
    }

};
