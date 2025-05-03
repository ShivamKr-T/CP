class disjointSet {
	vector<int> parent, size;
public:
	disjointSet(int n) {
		size.resize(n + 1, 1);
		parent.resize(n + 1);

		for (int i = 0; i <= n; i++) parent[i] = i;
	}

	int ultimateParent(int u) {
		if (u == parent[u]) return u;
		return parent[u] = ultimateParent(parent[u]);
	}

	void unite(int u, int v) {
		int ult_u = ultimateParent(u);
		int ult_v = ultimateParent(v);

		if (ult_u == ult_v) return;

		if (size[ult_u] < size[ult_v]) {
			parent[ult_u] = ult_v;
			size[ult_v] += size[ult_u];
		}

		else {
			parent[ult_v] = ult_u;
			size[ult_u] += size[ult_v];
		}
	}

};
