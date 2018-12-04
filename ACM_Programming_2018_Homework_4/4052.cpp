#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>

const int mx = 70000;
int n, a[20], b[mx], ntot, f[mx];

inline void work(int cs) {
    memset(f, 0, sizeof f);
    ntot = 0;
    scanf("%d", &n);
    if (n == 0) {
        exit(0);
    }
    for (int i = 1; i <= n; i++) {
        int tmp, cur;
        scanf("%d", &tmp);
        a[i] = (1 << (i - 1));
        for (int j = 1; j <= tmp; j++) {
            scanf("%d", &cur);
            a[i] |= (1 << (cur - 1));
        }
    }
    for (int s = 0; s < (1 << n); s++) {
        int cur = 0;
        for (int i = 1; i <= n; i++) {
            if (s & (1 << (i - 1))) {
                cur |= a[i];
            }
        }
        if (cur == (1 << n) - 1) {
            b[++ntot] = s;
            f[s] = 1;
        }
    }
    for (int s = 0; s < (1 << n); s++) {
        for (int j = s; j; j = (j - 1) & s) {
            f[s] = std::max(f[s], f[j] + f[s ^ j]);
        }
    }
    printf("Case %d: %d\n", cs, f[(1 << n) - 1]);
}

int main() {
    for (int i = 1; ; i++) {
        work(i);
    }
    return 0;
}
