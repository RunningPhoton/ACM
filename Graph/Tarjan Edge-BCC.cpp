int dfn[maxn], low[maxn], Index;
int Stack[maxn], top;
int Instack[maxn], Belong[maxn];
int bridge, block, cut[maxn << 1];
int head[maxn], nxt[maxn << 1], pnt[maxn << 1];

void Tarjan(int u,int pre){
	int v;
	low[u] = dfn[u] = ++Index;
	Stack[top++] = u;
	Instack[u] = 1;
	for(int i = head[u]; ~i ;i = nxt[i]){
		v = pnt[i];
		// 如果重边有效的话下面这句改成: if(v == pre && pre_num == 0){pre_num++;continue;} pre_num在for上面定义 int pre_num=0;
		if(v == pre)continue;
		if(!dfn[v]){
			Tarjan(v, u);
			low[u] = min(low[u], low[v]);
			if(low[v] > dfn[u]){
				bridge++;
				cut[i] = 1;
				cut[i ^ 1] = 1;
			}
		}
		else if(Instack[v]) low[u] = min(low[u], dfn[v]);
	}
	if(low[u] == dfn[u]){
		block++;
		do{
			v = Stack[--top];
			Instack[v] = false;
			Belong[v] = block;
		}while( v != u );
	}
}
