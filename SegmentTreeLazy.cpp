#include<bits/stdc++.h>
using namespace std;

template <class S,
          auto op,
          auto e,
          class F,
          auto mapping,
          auto composition,
          auto id>
struct lazy_segtree {
    static_assert(is_convertible_v<decltype(op), function<S(S, S)>>,
                  "op must work as S(S, S)");
    static_assert(is_convertible_v<decltype(e), function<S()>>,
                  "e must work as S()");
    static_assert(
        is_convertible_v<decltype(mapping), function<S(F, S)>>,
        "mapping must work as S(F, S)");
    static_assert(
        is_convertible_v<decltype(composition), function<F(F, F)>>,
        "composition must work as F(F, F)");
    static_assert(is_convertible_v<decltype(id), function<F()>>,
                  "id must work as F()");


public:
    lazy_segtree() : lazy_segtree(0) {}
    explicit lazy_segtree(int n) : lazy_segtree(vector<S>(n, e())) {}
    explicit lazy_segtree(const vector<S>& v) : _n(int(v.size())) {
        size = (int)bit_ceil((unsigned int)(_n));
        log = __builtin_ctz((unsigned int)size);
        d = vector<S>(2 * size, e());
        lz = vector<F>(size, id());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }

    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return e();

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        S sml = e(), smr = e();
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }

        return op(sml, smr);
    }

    S all_prod() { return d[1]; }

    void apply(int p, F f) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = mapping(f, d[p]);
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    void apply(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return;

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }

        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

private:
    int _n, size, log;
    vector<S> d;
    vector<F> lz;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, F f) {
        d[k] = mapping(f, d[k]);
        if (k < size) lz[k] = composition(f, lz[k]);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }
};

// Define our data type S and update type F
struct S {
    long long value;
    int len;  // Length of the segment
};

// Operations for lazy segtree
static S op(S a, S b) {
    return {a.value + b.value, a.len + b.len};
}
static S e() {
    return {0, 0};
}
static S mapping(long long f, S s) {
    return {s.value + f * s.len, s.len};
}
static long long composition(long long f, long long g) {
    return f + g;
}
static long long id() {
    return 0;
}

int main() {
    // Initialize array
    vector<S> v = {{1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}};
    int n = v.size();

    // Create lazy segment tree
    lazy_segtree<S, op, e, long long, mapping, composition, id> tree(v);

    // Test initial state
    cout << "Initial array: ";
    for (int i = 0; i < n; i++) cout << tree.get(i).value << " ";
    cout << "\n";
    cout << "Sum [0,5): " << tree.prod(0, 5).value << "\n\n";

    // Apply range update: add 10 to [0,2)
    tree.apply(0, 2, 10);
    cout << "After adding 10 to [0,2):\n";
    cout << "Element 0: " << tree.get(0).value << "\n";
    cout << "Element 1: " << tree.get(1).value << "\n";
    cout << "Sum [0,5): " << tree.prod(0, 5).value << "\n\n";

    // Apply point update: set element 3 to 10
    tree.set(3, {10, 1});
    cout << "After setting element 3 to 10:\n";
    cout << "Element 3: " << tree.get(3).value << "\n";
    cout << "Sum [0,5): " << tree.prod(0, 5).value << "\n\n";

    // Apply another range update: add 5 to [1,4)
    tree.apply(1, 4, 5);
    cout << "After adding 5 to [1,4):\n";
    for (int i = 0; i < n; i++)
        cout << "Element " << i << ": " << tree.get(i).value << "\n";
    cout << "Sum [0,5): " << tree.prod(0, 5).value << "\n";

    return 0;
}
