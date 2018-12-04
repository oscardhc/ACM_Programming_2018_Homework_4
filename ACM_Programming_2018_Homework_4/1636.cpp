#include <stdio.h>
#include <string.h>
#include <algorithm>

const int mx = 1e5 + 233;
int n, q;
char s[mx];

struct T {
    int tot = 0;
    struct N {
        int lson, rson, v, tag, sz;
        N *t;
        void pushdown();
        void asn(int k);
    }t[mx << 1];
    int build(int l, int r, N* _t, int id);
    void asn(int cur, int l, int r, int ql, int qr, int k);
    int qry(int cur, int l, int r, int ql, int qr);
}tree[7];

void T::N::pushdown() {
    if (lson) {
        if (tag == 0) {
            t[lson].asn(0);
            t[rson].asn(0);
        } else if (tag == 1) {
            t[lson].asn(1);
            t[rson].asn(1);
        }
    }
    tag = -1;
}
void T::N::asn(int k) {
    tag = k;
    v = k * sz;
}
int T::build(int l, int r, N* _t, int id) {
    int cur = ++tot;
    t[cur].t = _t;
    t[cur].tag = -1;
    if (l == r) {
        t[cur].v = s[l] - 'A' == id;
        t[cur].sz = 1;
        return cur;
    }
    int m = (l + r) >> 1;
    t[cur].lson = build(l, m, t, id);
    t[cur].rson = build(m + 1, r, t, id);
    t[cur].sz = t[t[cur].lson].sz + t[t[cur].rson].sz;
    t[cur].v = t[t[cur].lson].v + t[t[cur].rson].v;
    return cur;
}
void T::asn(int cur, int l, int r, int ql, int qr, int k) {
    if (ql > qr) {
        return;
    }
    if (l == ql && r == qr) {
        t[cur].asn(k);
        return;
    }
    if (t[cur].tag != -1) {
        t[cur].pushdown();
    }
    int m = (l + r) >> 1;
    if (ql <= m) {
        asn(t[cur].lson, l, m, ql, std::min(qr, m), k);
    }
    if (qr > m) {
        asn(t[cur].rson, m + 1, r, std::max(ql, m + 1), qr, k);
    }
    t[cur].v = t[t[cur].lson].v + t[t[cur].rson].v;
}
int T::qry(int cur, int l, int r, int ql, int qr) {
    if (ql > qr) {
        return 0;
    }
    if (l == ql && r == qr) {
        return t[cur].v;
    }
    if (t[cur].tag != -1) {
        t[cur].pushdown();
    }
    int m = (l + r) >> 1, ret = 0;
    if (ql <= m) {
        ret += qry(t[cur].lson, l, m, ql, std::min(qr, m));
    }
    if (qr > m) {
        ret += qry(t[cur].rson, m + 1, r, std::max(ql, m + 1), qr);
    }
    t[cur].v = t[t[cur].lson].v + t[t[cur].rson].v;
    return ret;
}

int main() {
    freopen("1636.in", "r", stdin);
    scanf("%s%d", s + 1, &q);
    n = strlen(s + 1);
    for (int i = 0; i < 7; i++) {
        tree[i].build(1, n, tree[i].t, i);
    }
    while (q--) {
        int l, r, flag = -1, c[7];
        scanf("%d%d", &l, &r);
        for (int i = 0; i < 7; i++) {
            if ((c[i] = tree[i].qry(1, 1, n, l, r)) & 1) {
                if (flag == -1) flag = i;
                else flag = 7;
            }
        }
        if (flag == 7) {
            continue;
        }
        int pl = l, pr = r;
        for (int i = 0; i < 7; i++) {
            if (c[i] == 0) {
                continue;
            }
            int cur = c[i] >> 1;
            tree[i].asn(1, 1, n, pl, pl + cur - 1, 1);
            tree[i].asn(1, 1, n, pr - cur + 1, pr, 1);
            tree[i].asn(1, 1, n, l, pl - 1, 0);
            tree[i].asn(1, 1, n, pr + 1, r, 0);
            tree[i].asn(1, 1, n, pl + cur, pr - cur, 0);
            pl += cur;
            pr -= cur;
        }
        if (flag != -1) {
            tree[flag].asn(1, 1, n, pl, pr, 1);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 7; j++) {
            if (tree[j].qry(1, 1, n, i, i)) {
                printf("%c", 'A' + j);
                break;
            }
        }
    }
    return 0;
}
