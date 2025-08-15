#include <bits/stdc++.h>
using namespace std;


template <class S, auto op, auto e> struct segtree {
    static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
                  "op must work as S(S, S)");
    static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
                  "e must work as S()");

public:
    segtree() : segtree(0) {}
    explicit segtree(int n) : segtree(std::vector<S>(n, e())) {}
    explicit segtree(const std::vector<S>& v) : _n(int(v.size())) {
        size = (int)bit_ceil((unsigned int)(_n));
        log = __builtin_ctz((unsigned int)size);
        d = std::vector<S>(2 * size, e());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) const {
        assert(0 <= p && p < _n);
        return d[p + size];
    }

    S prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        S sml = e(), smr = e();
        l += size;
        r += size;

        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() const { return d[1]; }

private:
    int _n, size, log;
    vector<S> d;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }

    unsigned int bit_ceil(unsigned int n) {
        unsigned int x = 1;
        while (x < n) x *= 2;
        return x;
    }
};

int op(int a, int b) { return a + b; }
int e() { return 0; }

int main() {
    vector<int> data = {1, 2, 3, 4, 8};
    segtree <int, op, e> seg(data);

    cout << "All elements sum: " << seg.all_prod() << "\n";     // 15
    cout << "Range [1,3) sum: " << seg.prod(1, 3) << "\n";      // 5 (2+3)
    cout << "Element at pos 2: " << seg.get(2) << "\n";         // 3

    seg.set(0, 10); // Change first element to 10
    cout << "After update:\n";
    cout << "All elements sum: " << seg.all_prod() << "\n";     // 24
    cout << "Range [0,2) sum: " << seg.prod(0, 2) << "\n";      // 12 (10+2)
    cout << "Single element [3,4): " << seg.prod(3, 4) << "\n"; // 4

    return 0;
}


/* (Something which I can remember) to_use -> segtree<int> seg(n, op, e); seg.build(arr);

template<typename S>
struct segtree {
    int n;
    vector<S> d;
    S (*op)(S, S);
    S (*e)();

    segtree(int _n, S (*_op)(S, S), S (*_e)()) : op(_op), e(_e) {
        n = 1;
        while (n < _n) n *= 2;
        d.assign(2 * n, e());
    }

    void build(const vector<S>& v) {
        for (int i = 0; i < (int)v.size(); ++i) d[n + i] = v[i];
        for (int i = n - 1; i > 0; --i)
            d[i] = op(d[2 * i], d[2 * i + 1]);
    }

    void set(int p, S x) {
        p += n;
        d[p] = x;
        while (p > 1) {
            p >>= 1;
            d[p] = op(d[2 * p], d[2 * p + 1]);
        }
    }

    S get(int p) {
        return d[p + n];
    }

    S prod(int l, int r) {
        S sml = e(), smr = e();
        l += n; r += n;
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1; r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() {
        return d[1];
    }
};

*/
