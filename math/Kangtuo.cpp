int fac[10] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
int use[10];

string Kangtuo(int x) {
    CLR(use);
    string res = "";
    for (int i = 8; ~i; i--) {
        int d = x / fac[i];
        for (int i = 0; i <= d; i++) if (use[i]) d++;
        res += d + '1';
        use[d] = 1;
        x %= fac[i];
    }
    return res;
}

int kangtuo(string &x) {
    CLR(use);int res = 0;
    for (int i = 0; x[i]; i++) {
        int t = x[i] - '0', d = t--;
        for (int j = 1; j < d; j++) if (use[j]) t--;
        res += t * fac[8 - i];
        use[d] = 1;
    }
    return res;
}