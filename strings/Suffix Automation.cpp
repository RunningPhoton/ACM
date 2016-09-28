
const int maxnode = maxn * 2;
char s[maxn];


class Suffix_Automation{
public:
	int ch[maxnode][max_index];
	int par[maxnode], len[maxnode];
	int index[maxnode], C[maxnode];
	int mi[maxnode], ma[maxnode];
	int cur, last;

	void node(int v = 0) {
		len[++cur] = v;
		ma[cur] = 0;
		mi[cur] = inf;
		memset(ch[cur], 0x00, sizeof ch[cur]);
		par[cur] = 0;
	}
	void show_tags(){
		puts("Tags: pay attention to the value of max_index!");
		puts("Tags: pay attention to the value of maxn!");
		puts("Tags: pay attention to the value of id!");
	}

	void init() {show_tags(); cur = -1, last = 0; node(); }

	Suffix_Automation() {init(); }

	void clone(int l, int r) {
		par[l] = par[r];
		memcpy(ch[l], ch[r], sizeof ch[l]);
	}

	int idx(char c) {return c - 'a'; }

	void toposort(){
		memset(C, 0, sizeof C);
		for (int i = 1; i <= cur; i++) C[len[i]]++;
		for (int i = 1; i <= cur; i++) C[i] += C[i-1];
		for (int i = 1; i <= cur; i++) index[C[len[i]]--] = i;
	}

	void add(char c) {
		int id = idx(c);  // pay attention!
		node(len[last]+1);
		int p = last, np = last = cur; 
		while (p && !ch[p][id]) ch[p][id] = np, p = par[p];
		if (!ch[p][id]) ch[p][id] = np;
		else {
			int q = ch[p][id];
			if (len[q] == len[p] + 1) par[np] = q;
			else {
				node(len[p] + 1);
				int nq = cur;
				clone(nq, q);
				par[q] = par[np] = nq;
				while (p && ch[p][id] == q) ch[p][id] = nq, p = par[p];
				if (ch[p][id] == q) ch[p][id] = nq;
			}
		}
	}

	int solve() {
		while (~scanf("%s", s)) {
			int tmp = 0, u = 0;
			for (int i = 0; s[i]; i++) {
				int id = idx(s[i]);
				while (u && !ch[u][id]) u = par[u];
				tmp = min(len[u], tmp);
				u = ch[u][id]; if(u)tmp++;
				ma[u] = max(ma[u], tmp);
			}
			for (int i = cur; ~i; i--) {
				int id = index[i];
				if (mi[id] > ma[id]) mi[id] = ma[id];
				int q = par[id];
				ma[q] = min(len[q], max(ma[q], ma[id]));
				ma[id] = 0;
			}
		}
		int res = 0;
		for (int i = 0; i <= cur; i++) res = max(res, mi[i]);
		return res;
	}

} sam;