constexpr int mod = 1e9 + 7;

int power(int x, int y) {
	int res = 1; x = x % mod;
	if (x == 0) return 0ll;
	while (y > 0) {
		if (y & 1) res = (res * x) % mod;
		y = y >> 1;
		x = (x * x) % mod;
	}
	return res;
}
