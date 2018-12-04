#include <bits/stdc++.h>

const int mx = 1e5 + 233;
int n, m, f[mx];
long long ans = 0;

inline int gtf (int x) {
    return f[x] < 0 ? x : f[x] = gtf(f[x]) ;
}

int main(){
    scanf("%d%d", &n, &m);
    memset(f, -1, sizeof f);
    for (int i = 1; i <= m; i++) {
        int s, t;
        scanf("%d%d", &s, &t);
        s = gtf(s);
        t = gtf(t);
        if (s != t) {
            f[t] += f[s];
            f[s] = t;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (f[i] < 0) {
            ans += 1ll * f[i] * (f[i] + 1) / 2;
        }
    }
    printf("%lld\n", ans - m);
    return 0;
}
