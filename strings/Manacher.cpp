char  s[maxn], t[maxn];
int p[maxn];

int Insert(){
    t[0] = '#';t[1] = '@';
    int tot = 2;
    for (int i = 0; s[i]; i++){
         t[tot++] = s[i];
         t[tot++] = '@';
    }
    return tot;
}


void Manacher(){
    int mx = 0, id = 0;
    for (int i = 1; t[i]; i++) {
        p[i] = mx > i ? min(mx - i, p[id * 2 - i]) : 1;
        while (t[i-p[i]] == t[i+p[i]]) p[i]++;
        if (mx < i + p[i]) mx = i+p[i], id = i;
    }
}
