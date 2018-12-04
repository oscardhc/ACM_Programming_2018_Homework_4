#include <stdio.h>
#include <string.h>
#include <algorithm>

long long n, a[20], ans;

int main() {
    scanf("%lld", &n);
    a[0] = 1;
    for (int i = 1; i <= 18; i++) {
        a[i] = a[i - 1] * 10;
    }
    while (n) {
        long long tmp = n;
        int ma = 0, bs = 0, cubs = 0;
        while (tmp) {
            if (tmp % 10 > ma) {
                ma = tmp % 10;
                bs = cubs;
            }
            cubs++;
            tmp /= 10;
        }
        if (ma == 9) {
            long long hhh = n % a[bs] / 9 + 1;
            ans += hhh;
            n -= hhh * 9;
        } else {
            ans += 1;
            n -= ma;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
