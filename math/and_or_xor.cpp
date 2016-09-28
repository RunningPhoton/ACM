
// 三种集合幂卷积的正变换和逆变换
void fwtXor(ll* a, int len) {
    if(len == 1) return;
    int h = len >> 1;
    fwtXor(a, h);
    fwtXor(a + h, h);
    for(int i = 0; i < h; ++i) {
        ll x1 = a[i];
        ll x2 = a[i + h];
        a[i] = (x1 + x2) % MOD;
        a[i + h] = (x1 - x2 + MOD) % MOD;
    }
}

void ifwtXor(ll* a, int len) {
    if(len == 1) return;
    int h = len >> 1;
    for(int i = 0; i < h; ++i) {
        // y1=x1+x2
        // y2=x1-x2
        ll y1 = a[i];
        ll y2 = a[i + h];
        a[i] = (y1 + y2) * invTwo % MOD;
        a[i + h] = (y1 - y2 + MOD) * invTwo % MOD;
    }
    ifwtXor(a, h);
    ifwtXor(a + h, h);
}

void fwtAnd(ll* a, int len) {
    if(len == 1) return;
    int h = len >> 1;
    fwtAnd(a, h);
    fwtAnd(a + h, h);
    for(int i = 0; i < h; ++i) {
        ll x1 = a[i];
        ll x2 = a[i + h];
        a[i] = (x1 + x2) % MOD;
        a[i + h] = x2;
    }
}

void ifwtAnd(ll* a, int len) {
    if(len == 1) return;
    int h = len >> 1;
    for(int i = 0; i < h; ++i) {
        // y1=x1+x2
        // y2=x2
        ll y1 = a[i];
        ll y2 = a[i + h];
        a[i] = (y1 - y2 + MOD) % MOD;
        a[i + h] = y2;
    }
    ifwtAnd(a, h);
    ifwtAnd(a + h, h);
}

void fwtOr(ll* a, int len) {
    if(len == 1) return;
    int h = len >> 1;
    fwtOr(a, h);
    fwtOr(a + h, h);
    for(int i = 0; i < h; ++i) {
        ll x1 = a[i];
        ll x2 = a[i + h];
        a[i] = x1;
        a[i + h] = (x2 + x1) % MOD;
    }
}

void ifwtOr(ll* a, int len) {
    if(len == 1) return;
    int h = len >> 1;
    for(int i = 0; i < h; ++i) {
        // y1=x1
        // y2=x2+x1
        ll y1 = a[i];
        ll y2 = a[i + h];
        a[i] = y1;
        a[i + h] = (y2 - y1 + MOD) % MOD;
    }
    ifwtOr(a, h);
    ifwtOr(a + h, h);
}