class LazySegmentTree {
public:
    vector<int> seg, lazy;
    int n;

    LazySegmentTree(vector<int>& arr) {
        n = arr.size();
        seg.resize(4 * n + 1);
        lazy.resize(4 * n + 1, 0);
        build(0, 0, n - 1, arr);
    }

    void build(int ind, int low, int high, vector<int> &arr) {
        if (low == high) {
            seg[ind] = arr[low];
            return;
        }

        int mid = (low + high) / 2;
        build(2 * ind + 1, low, mid, arr);
        build(2 * ind + 2, mid + 1, high, arr);
        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }

    void push(int ind, int low, int high) {
        if (lazy[ind] != 0) {
            seg[ind] += (high - low + 1) * lazy[ind];
            if (low != high) {
                lazy[2 * ind + 1] += lazy[ind];
                lazy[2 * ind + 2] += lazy[ind];
            }
            lazy[ind] = 0;
        }
    }

    void rangeUpdate(int ind, int low, int high, int l, int r, int val) {
        push(ind, low, high);

        if (r < low || high < l) return;
        if (l <= low && high <= r) {
            lazy[ind] += val;
            push(ind, low, high);
            return;
        }

        int mid = (low + high) / 2;
        rangeUpdate(2 * ind + 1, low, mid, l, r, val);
        rangeUpdate(2 * ind + 2, mid + 1, high, l, r, val);
        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }

    int rangeQuery(int ind, int low, int high, int l, int r) {
        push(ind, low, high);

        if (r < low || high < l) return 0;
        if (l <= low && high <= r) return seg[ind];

        int mid = (low + high) / 2;
        auto left = rangeQuery(2 * ind + 1, low, mid, l, r);
        auto right = rangeQuery(2 * ind + 2, mid + 1, high, l, r);
        return left + right;
    }

    void update(int l, int r, int val) { rangeUpdate(0, 0, n - 1, l, r, val); }
    int query(int l, int r) { return rangeQuery(0, 0, n - 1, l, r); }
};
