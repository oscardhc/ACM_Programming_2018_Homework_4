#include <stdio.h>
#include <string.h>
#include <queue>

const int mx = 105, inf = 0x3f3f3f3f;
const int dx[] = {0, 0, -1, 1};
const int dy[] = {-1, 1, 0, 0};
int n, m, tot = 1, S = 1, T = 2, d[mx * mx], fir[mx * mx], ans;
struct E {
    int t, nx, f;
}e[mx * mx * 10];

inline void add(int _s, int _t, int _f) {
    e[++tot] = E{_t, fir[_s], _f}, fir[_s] = tot;
    e[++tot] = E{_s, fir[_t],  0}, fir[_t] = tot;
}

std::queue<int> q;
inline int bfs() {
    while (!q.empty()) q.pop();
    memset(d, -1, sizeof d);
    d[S] = 0;
    q.push(S);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int i = fir[cur]; i; i = e[i].nx) {
            if (e[i].f > 0 && d[e[i].t] == -1) {
                d[e[i].t] = d[cur] + 1;
                q.push(e[i].t);
            }
        }
    }
    return d[T] != -1;
}
inline int dfs(int cur, int fl) {
    if (cur == T) {
        return fl;
    }
    int used = 0;
    for (int i = fir[cur]; i; i = e[i].nx) {
        if (e[i].f > 0 && d[e[i].t] == d[cur] + 1) {
            int tmp = dfs(e[i].t, std::min(fl - used, e[i].f));
            used += tmp;
            e[i].f -= tmp;
            e[i^1].f += tmp;
            if (used == fl) {
                return used;
            }
        }
    }
    if (!used) {
        d[cur] = -1;
    }
    return used;
}
inline int id(int i, int j) {
    return i * 101 + j;
}

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int tmp;
            scanf("%d", &tmp);
            ans += tmp;
            if ((i + j) & 1) {
                add(id(i, j), T, tmp);
            } else {
                add(S, id(i, j), tmp);
                for (int k = 0; k < 4; k++) {
                    int x = i + dx[k], y = j + dy[k];
                    if (x < 1 || y < 1 || x > n || y > m) {
                        continue;
                    }
                    add(id(i, j), id(x, y), inf);
                }
            }
        }
    }
    while (bfs()) ans -= dfs(S, inf);
    printf("%d\n", ans);
    return 0;
}
