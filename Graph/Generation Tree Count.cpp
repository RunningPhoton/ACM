typedef long long ll;  
int deg[maxn];  
ll C[N][N]; // C = D - G
  
ll det(ll a[][N], int n) {  
    ll res = 1;  
    for(int i = 1; i < n; i++) {  
        for(int j = i + 1; j < n; j++)  
            while(a[j][i]) {  
                ll t = a[i][i] / a[j][i];  
                for(int k = i; k < n; k++)  
                    a[i][k] = (a[i][k] - a[j][k] * t);  
                for(int k = i; k < n; k++)  
                    swap(a[i][k], a[j][k]);  
                res = -res;  
            }  
        if(!a[i][i]) return 0;
        res = res * a[i][i];  
    }  
    if(res < 0) res = -res;
    return res;  
}  