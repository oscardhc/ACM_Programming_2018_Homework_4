#include <stdio.h>
#include <algorithm>
#include <string.h>

const int mx = 1 << 20;
int n, f[mx + 233];
char str[25];

int main() {
    n = 10;
    for (int s = 0; s < (1 << n); s++) {
        for (int i = 1; i < n; i++) {
            if ((s >> i & 1) == 1 && (s >> (i-1) & 1) == 0) {
                int ns = s ^ (1 << i) ^ (1 << (i-1));
                if (f[ns] == 0) {
                    f[s] = 1;
                }
            }
        }
        for (int i = 2; i < n; i++) {
            if ((s >> i & 1) == 1 && (s >> (i-1) & 1) == 1 && (s >> (i-2) & 1) == 0 ) {
                int ns = s ^ (1 << i) ^ (1 << (i-2));
                if (f[ns] == 0) {
                    f[s] = 1;
                }
            }
        }
    }
    for (int s = 0; s < (1 << n); s++) {
        int cu = s, hhh = 0;
        for (int i = 0; i < n; i++) {
            printf("%d", cu & 1);
            if (cu & 1) hhh += i;
            cu >>= 1;
        }
        printf("       %d %d\n", hhh%3, f[s]);
    }
    // int t;scanf("%d", &t);
    // while (t--) {
    //     scanf("%s", str);
    //     int m = strlen(str), tmp = 0;
    //     int hhh = 0;
    //     for (int i = 0; i < m; i++) {
    //         tmp = tmp * 2 + (str[m - i - 1] == 'o');
    //         hhh += i * (str[i] == 'o');
    //     }
    //     printf("(%d)\n", hhh % 3);
    //     printf("%s\n", f[tmp] ? "Hou" : "Su");
    // }
    return 0;
}
