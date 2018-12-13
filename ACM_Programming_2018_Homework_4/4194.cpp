#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>

long long n, ans, tot;int a[20], lst;
long long f[10][20][10], g[10][20][10];

std::pair<long long, long long> cal(int i, int j, int k) {
    if (~f[i][j][k]) return {f[i][j][k], g[i][j][k]};
    if (j == 0) {
        if (i <= k) return {2, 10 - i};
        else return {1, 10 + k - i};
    }
    f[i][j][k] = 0;
    g[i][j][k] = k;
    for (int l = 9; l >= 0; l--) {
        auto ret = cal(std::max(l, i), j - 1, g[i][j][k]);
        f[i][j][k] += ret.first;
        g[i][j][k] = ret.second;
    }
    return {f[i][j][k], g[i][j][k]};
}

int main() {
    scanf("%lld", &n);
    if (n < 10) {
        std::cout << (n ? 1 : 0) << std::endl;
        return 0;
    }
    while (n) {
        a[tot++] = n % 10;
        n /= 10;
    }
    memset(f, -1, sizeof(f));
    lst = a[0];
    for (int i = 1; i < tot; i++) {
        int ma = 0;
        for (int j = tot - 1; j > i; j--) {
            ma = std::max(ma, a[j]);
        }
        for (int j = i == 1 ? a[i] : a[i] - 1; j >= 0; j--) {
            auto ret = cal(std::max(ma, j), i - 1, lst);
            ans += ret.first;
            lst = ret.second;
        }
    }
    std::cout << ans - 1 << std::endl;
    return 0;
}
