#include <bits/stdc++.h>
using namespace std;

template <class S, auto op>
struct sparsetable {
    int n, LOG;
    vector<vector<S>> st;

    sparsetable() = default;

    explicit sparsetable(const vector<S>& a) {
        n = a.size();
        LOG = 32 - __builtin_clz(n); // if ll use 64
        st.assign(LOG, vector<S>(n));
        st[0] = a;
        for (int j = 1; j < LOG; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                st[j][i] = op(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    S prod(int l, int r) const {
        assert(0 <= l && l < r && r <= n);
        int j = 31 - __builtin_clz(r - l); // if ll use 63
        return op(st[j][l], st[j][r - (1 << j)]); // [l, r-1].
    }

    S all_prod() {
        if (n == 0) return e();
        return prod(0, n);
    }
};

int op(int a, int b) {
    return gcd(a, b);
}


int main() {
    vector<int> a = {5, 9, 9, 6, 2, 7};
    sparsetable<int, op> st(a);

    cout << st.prod(1, 4) << '\n'; // prints minimum from index 1 to 3 (inclusive), i.e., min(3,8,6) = 3
}
