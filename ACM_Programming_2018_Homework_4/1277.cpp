#include <bits/stdc++.h>
#include <math.h>

const int mx = 1e5 + 233;
int n, w, f, a[mx], ans = mx;

inline int chk (int k) {
    int ls = 0, ret = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] - ls > k) {
            ret += (ls - a[i]);
            ls = ls + k;
        } else {
            ls = a[i];
        }
    }
    return ret;
}

int main(){
    scanf("%d%d%d", &n, &w, &f);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for (int l = 1, r = w; l <= r; ) {
        int m = (l + r) >> 1;
        if (chk(m) <= f) ans = m, l = m + 1;
        else r = m - 1;
    }
    printf("%d\n", ans);
    return 0;
}
