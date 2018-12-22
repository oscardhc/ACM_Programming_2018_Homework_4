#include <stdio.h>
#include <algorithm>
#include <string.h>

const int mx = 1e5 + 233;
int n, cnt[mx];
char str[mx];

int main() {
    int t;scanf("%d", &t);
    while (t--) {
        memset(cnt, 0, sizeof cnt);
        scanf("%s", str);
        int m = strlen(str), tmp = 0, ans = 0;
        for (int i = 0; i < m; i++) {
            if (str[i] == '.') {
                tmp = tmp + 1;
            } else {
                cnt[tmp]++;
            }
        }
        for (int i = 1 ; i < m; i += 2) {
            ans = ans ^ (cnt[i] % 3);
        }
        printf("%s\n", ans ? "Hou" : "Su");
    }
    return 0;
}
