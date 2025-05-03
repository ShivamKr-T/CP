vi sieve(int n) {
	vector<bool> prime(n + 1, true);
	prime[0] = prime[1] = false;
	for (int p = 2; p * p <= n; p++) {
		if (prime[p]) {
			for (int i = p * p; i <= n; i += p) prime[i] = false;
		}
	}
	vi ans;
	for (int p = 2; p <= n; p++) {
		if (prime[p]) ans.pb(p);
	}
	return ans;
}
