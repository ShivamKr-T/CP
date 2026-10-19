#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
public:
    vector<int> seg;
    int n;
    SegmentTree(vector<int> &arr) {
        n = arr.size();
        seg.resize(4 * n + 1, 0);
        build(0, 0, n - 1, arr);
    }
    void build(int ind, int low, int high, vector<int> &arr)
    {
        if (low == high) {
            seg[ind] = arr[low];
            return;
        }

        int mid = (low + high) / 2;
        build(2 * ind + 1, low, mid, arr);
        build(2 * ind + 2, mid + 1, high, arr);
        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
        return;
    }

    void update(int ind, int low, int high, int pos, int val)
    {
        if (low == high) {
            seg[ind] = val;
            return;
        }

        int mid = (low + high) / 2;
        if (pos <= mid) update(2 * ind + 1, low, mid, pos, val);
        else update(2 * ind + 2, mid + 1, high, pos, val);

        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }

    int query(int ind, int low, int high, int l, int r) {
        if (low > r || high < l) return 0;

        if (low >= l && high <= r) return seg[ind];

        int mid = (low + high) / 2;
        int left = query(2 * ind + 1, low, mid, l, r);
        int right = query(2 * ind + 2, mid + 1, high, l, r);
        return left + right;     // based on requirement (can be +,min,max,gcd,etc.)
    }

    void update(int pos, int val) { update(0, 0, n - 1, pos, val); }
    int query(int l, int r) { return query(0, 0, n - 1, l, r); }

};
