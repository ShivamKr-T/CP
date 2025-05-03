class SegmentTree {
public:
	vector<int> seg, lazy;
	SegmentTree(int n) {
		seg.resize(4 * n + 1, 0);
		lazy.resize(4 * n + 1, 0);
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

	void rangeUpdate(int ind, int low, int high, int l, int r, int val) {
		if (lazy[ind] != 0) {
			seg[ind] += (high - low + 1) * lazy[ind];
			if (low != high) {
				lazy[2 * ind + 1] += lazy[ind];
				lazy[2 * ind + 2] += lazy[ind];
			}
			lazy[ind] = 0;
		}
		if (r < low || l > high || low > high) return;

		if (low >= l && high <= r) {
			seg[ind] += (high - low + 1) * val;
			if (low != high) {
				lazy[2 * ind + 1] += val;
				lazy[2 * ind + 2] += val;
			}
			return;
		}
		int mid = (low + high) / 2;
		rangeUpdate(2 * ind + 1, low, mid, l, r, val);
		rangeUpdate(2 * ind + 2, mid + 1, high, l, r, val);
		seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
	}

	void update(int ind, int low, int high, int i, int val)
	{
		if (low == high) {
			seg[ind] = val;
			return;
		}

		int mid = (low + high) / 2;
		if (i <= mid) update(2 * ind + 1, low, mid, i, val);
		else update(2 * ind + 2, mid + 1, high, i, val);

		seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
		return;
	}

	int lazyQuery(int ind, int low, int high, int l, int r) {
		if (lazy[ind] != 0) {
			seg[ind] += (high - low + 1) * lazy[ind];
			if (low != high) {
				lazy[2 * ind + 1] += lazy[ind];
				lazy[2 * ind + 2] += lazy[ind];
			}
			lazy[ind] = 0;
		}
		if (r < low || l > high || low > high) return 0;

		if (low >= l && high <= r) {
			return seg[ind];
		}
		int mid = (low + high) / 2;
		return lazyQuery(2 * ind + 1, low, mid, l, r) + lazyQuery(2 * ind + 2, mid + 1, high, l, r);
	}

	int query(int ind, int low, int high, int l, int r) {
		if (low > r || high < l) return 0;

		if (low >= l && high <= r) return seg[ind];

		int mid = (low + high) / 2;
		int left = query(2 * ind + 1, low, mid, l, r);
		int right = query(2 * ind + 2, mid + 1, high, l, r);
		return left + right;
	}

};
