int smallest_string(string s){
    int len = s.size();
    s = s + s;
    int i = 0, j = 1, k;
    while (i < len && j < l) {
        for (k = 0; k < l; k++)
            if (s[i + k] != s[j + k]) break;
        if (k == l) break;
        if (s[i + k] > s[j + k]) i = i + k + 1;
        else if (s[i + k] < s[j + k]) j = j + k + 1;
        if (i == j) j++;
    }
    return min(i, j);
}
