#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <queue>

const int mx = 35;
const int inf = 0x3f3f3f3f;
int n, m, nn, l[mx], r[mx], u[mx], d[mx], e[mx][mx], ans[mx], bk[mx], in[mx];
char str[mx][mx];
std::vector<int> v;

inline void dfs(int cur) {
    if (cur == nn) {
        for (int i = 0; i < nn; i++) {
            printf("%c", ans[i] + 'A');
        }
        printf("\n");
    }
    for (int i = 0; i < nn; i++) {
        if (in[i] == 0 && bk[i] == 0) {
            bk[i] = 1;
            for (int j = 0; j < nn; j++) {
                if (e[v[i]][v[j]]) {
                    in[j]--;
                }
            }
            ans[cur] = v[i];
            dfs(cur + 1);
            for (int j = 0; j < nn; j++) {
                if (e[v[i]][v[j]]) {
                    in[j]++;
                }
            }
            bk[i] = 0;
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%s", str[i] + 1);
    }
    memset(l, inf, sizeof l);
    memset(u, inf, sizeof u);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (str[i][j] != '.') {
                l[str[i][j] - 'A'] = std::min(l[str[i][j] - 'A'], i);
                r[str[i][j] - 'A'] = std::max(r[str[i][j] - 'A'], i);
                u[str[i][j] - 'A'] = std::min(u[str[i][j] - 'A'], j);
                d[str[i][j] - 'A'] = std::max(d[str[i][j] - 'A'], j);
            }
        }
    }
    for (int k = 0; k <= 26; k++) {
        if (l[k] == inf) continue;
        for (int i = l[k]; i <= r[k]; i++) {
            if (str[i][u[k]] != k + 'A') {
                e[k][str[i][u[k]] - 'A'] = 1;
            }
            if (str[i][d[k]] != k + 'A') {
                e[k][str[i][d[k]] - 'A'] = 1;
            }
        }
        for (int j = u[k]; j <= d[k]; j++) {
            if (str[l[k]][j] != k + 'A') {
                e[k][str[l[k]][j] - 'A'] = 1;
            }
            if (str[r[k]][j] != k + 'A') {
                e[k][str[r[k]][j] - 'A'] = 1;
            }
        }
        v.push_back(k);
    }
    nn = v.size();
    for (int i = 0; i < nn; i++) {
        for (int j = 0; j < nn; j++) {
            if (e[v[i]][v[j]]) {
                in[j]++;
            }
        }
    }
    dfs(0);
    return 0;
}
