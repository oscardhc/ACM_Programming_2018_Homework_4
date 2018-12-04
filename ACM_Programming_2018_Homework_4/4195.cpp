#include <bits/stdc++.h>

const int mx = 1e5 + 233;
const int mod = 1e9 + 7;

int n, tot, fir[mx], v[mx], ans[mx];
struct E {
    int t, nx;
}e[mx << 1];

int f[mx][17], d[mx], dep[mx];
inline void dfs(int cur) {
    for (int i = 1; i < 17; i++) {
        f[cur][i] = f[f[cur][i - 1]][i - 1];
    }
    for (int i = fir[cur]; i; i = e[i].nx) {
        if (e[i].t != f[cur][0]) {
            f[e[i].t][0] = cur;
            dep[e[i].t] = dep[cur] + v[e[i].t];
            d[e[i].t] = d[cur] + 1;
            dfs(e[i].t);
        }
    }
}
inline int lca(int x, int y) {
    if (d[x] < d[y]) std::swap(x, y);
    for (int i = 16; i >= 0; i--) {
        if (d[f[x][i]] >= d[y]) x = f[x][i];
    }
    if (x == y) return x;
    for (int i = 16; i >= 0; i--) {
        if (f[x][i] && f[x][i] != f[y][i]) {
            x = f[x][i];
            y = f[y][i];
        }
    }
    return f[x][0];
}

inline int dis(int x, int y) {
    int l = lca(x, y);
    return dep[x] + dep[y] - dep[l] - dep[f[l][0]];
}

inline void ade(int x, int y) {
    e[++tot] = E{y, fir[x]}, fir[x] = tot;
    e[++tot] = E{x, fir[y]}, fir[y] = tot;
}

int xx[mx], yy[mx], o[mx], ff[mx], dd[mx][2], len[mx];
inline int gtf(int x) {
    return ff[x] == x ? x : ff[x] = gtf(ff[x]);
}

inline int pw(int x, int y) {
    int ret = 1;
    for (; y; y >>= 1, x = 1ll * x * x % mod) if (y & 1) ret = 1ll * ret * x % mod;
    return ret;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
    }
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &xx[i], &yy[i]);
        ade(xx[i], yy[i]);
    }
    dep[1] = v[1];
    d[1] = 1;
    dfs(1);
    for (int i = 1; i < n; i++) {
        scanf("%d", &o[i]);
    }
    ans[n] = 1;
    for (int i = n; i >= 1; i--) {
        dd[i][0] = i;
        ff[i] = i;
        len[i] = v[i];
        ans[n] = 1ll * ans[n] * v[i] % mod;
    }
    for (int i = n - 1; i >= 1; i--) {
        int f1 = gtf(xx[o[i]]), f2 = gtf(yy[o[i]]);
        int ma = 0, tx = 0, ty = 0;
        if (len[f1] > len[f2]) {
            ma = len[f1];
            tx = dd[f1][0];
            ty = dd[f1][1];
        } else {
            ma = len[f2];
            tx = dd[f2][0];
            ty = dd[f2][1];
        }
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                if (!dd[f1][j] || !dd[f2][k]) continue;
                int cur = dis(dd[f1][j], dd[f2][k]);
                if (cur > ma) {
                    ma = cur;
                    tx = dd[f1][j];
                    ty = dd[f2][k];
                }
            }
        }
        ans[i] = 1ll * ans[i + 1] * pw(len[f1], mod - 2) % mod * pw(len[f2], mod - 2) % mod * ma % mod;
        dd[f1][0] = tx;
        dd[f1][1] = ty;
        len[f1] = ma;
        ff[f2] = f1;
    }
    for (int i = 1; i <= n; i++) {
        printf("%d\n", ans[i]);
    }
    return 0;
}
