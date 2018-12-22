#include <stdio.h>
#include <string.h>
#include <algorithm>

const int mx = 1e5 + 233;
const int inf = 0x3f3f3f3f;
int n, w, ff, a[mx], ans = mx;
int f[mx][105];

inline int chk(int l) {
    memset(f, inf, sizeof f);
    int ret = inf;
    f[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= w; j++) {
            for (int k = 0; k <= l; k++) {
                if (j - k >= 0) {
                    f[i][j] = std::min(f[i][j], f[i - 1][j - k] + std::abs(j - a[i]));
                }
            }
            if (w - j <= l) {
                ret = std::min(ret, f[i][j]);
            }
        }
    }
    return ret;
}

int main(){
    scanf("%d%d%d", &n, &w, &ff);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    std::sort(a + 1, a + 1 + n);
    for (int l = 1, r = w; l <= r; ) {
        int m = (l + r) >> 1;
        if (chk(m) <= ff) ans = m, r = m - 1;
        else l = m + 1;
    }
    printf("%d\n", ans);
    return 0;
}
