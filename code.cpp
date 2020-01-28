#include <bits/stdc++.h>

#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,tune=native")
#pragma GCC optimize("unroll-loops")


using namespace std;

struct line {
    long long a, b;
};

const int N = 1e6 + 36;

long long pref[N];
line tree[N * 4];
int p = 1, h[N];

void add(line x, int v, int l, int r){
    int mid = (l + r) >> 1;
    long long M, L, R;
    M = (tree[v].a - x.a) * mid + (tree[v].b - x.b);
    if (M >= 0){
        swap(x, tree[v]);
    }
    if (l == r){
        return;
    }
    L = (x.a - tree[v].a) * l + (x.b - tree[v].b);
    if (0 > L){
        add(x, v << 1, l, mid);
    }
    R = (x.a - tree[v].a) * r + (x.b - tree[v].b);
    if (0 > R){
        add(x, v << 1 | 1, mid + 1, r);
    }
}

inline long long fin(int x){
    int v = x + p;
    long long ans = tree[v].a * x + tree[v].b;
    v >>= 1;
    while (v){
        ans = min(ans, tree[v].a * x + tree[v].b);
        v >>= 1;
    }
    return ans;
}




signed main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#else
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
#endif // LOCAL
    int n, y;
    cin >> n >> y;
    string s;
    cin >> s;
    long long z = 0, all = 0;
    for (int i(0); i < n; ++i) {
        if (i) pref[i] = pref[i - 1];
        if (s[i] != '+') {
            all += pref[i];
            if (pref[i] > 0) {
                h[z++] = i;
            }
        } else
        ++pref[i];
    }
    while (p <= z){
        p <<= 1;
    }
    line strt;
    strt.a = 0, strt.b = 0;
    add(strt, 1, 0, p - 1);
    for (int i(0); i < z; ++i){
        long long x = fin(i);
        line nw;
        nw.a = -pref[h[i]];
        nw.b = x + y - 1ll * i * nw.a;
        add(nw, 1, 0, p - 1);
    }
    cout << all + fin(z);
    return 0;
}
