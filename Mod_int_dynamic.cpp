#include <bits/stdc++.h>
using namespace std;

// ------------ Internal Utilities (Minimal mock for demonstration) -------------
namespace internal {

template <class T> using is_signed_int_t = enable_if_t<is_signed<T>::value>;
template <class T> using is_unsigned_int_t = enable_if_t<is_unsigned<T>::value>;

template <typename T>
T safe_mod(T x, T m) {
	x %= m;
	if (x < 0) x += m;
	return x;
}

// Barrett reduction for fast modulo multiplication
struct barrett {
	unsigned int m;
	unsigned long long im;

	explicit barrett(unsigned int m) : m(m), im((unsigned long long)(-1) / m + 1) {}

	unsigned int umod() const { return m; }

	unsigned int mul(unsigned int a, unsigned int b) const {
		unsigned long long z = a;
		z *= b;
		unsigned long long x = ((unsigned __int128)z * im) >> 64;
		unsigned int v = (unsigned int)(z - x * m);
		return v >= m ? v - m : v;
	}
};

// Extended GCD to compute modular inverse
pair<long long, long long> inv_gcd(long long a, long long b) {
	a = safe_mod(a, b);
	if (a == 0) return {b, 0};

	long long s = b, t = a;
	long long m0 = 0, m1 = 1;

	while (t) {
		long long u = s / t;
		s -= t * u; swap(s, t);
		m0 -= m1 * u; swap(m0, m1);
	}
	if (m0 < 0) m0 += b / s;
	return {s, m0};
}

struct modint_base {};
struct static_modint_base : modint_base {};

template<int m> constexpr bool is_prime = (m == 998244353 || m == 1000000007); // Optional simplification

} // namespace internal

// ------------------ Dynamic Modint -------------------
template <int id>
struct dynamic_modint {
	using mint = dynamic_modint;

	static int mod() { return (int)(bt.umod()); }
	static void set_mod(int m) { bt = internal::barrett(m); }

	static mint raw(int v) { mint x; x._v = v; return x; }

	dynamic_modint() : _v(0) {}

	template <class T, internal::is_signed_int_t<T>* = nullptr>
	dynamic_modint(T v) {
		long long x = v % (long long)(mod());
		if (x < 0) x += mod();
		_v = (unsigned int)(x);
	}

	template <class T, internal::is_unsigned_int_t<T>* = nullptr>
	dynamic_modint(T v) {
		_v = (unsigned int)(v % mod());
	}

	unsigned int val() const { return _v; }

	mint& operator+=(const mint& rhs) {
		_v += rhs._v;
		if (_v >= mod()) _v -= mod();
		return *this;
	}

	mint& operator-=(const mint& rhs) {
		_v += mod() - rhs._v;
		if (_v >= mod()) _v -= mod();
		return *this;
	}

	mint& operator*=(const mint& rhs) {
		_v = bt.mul(_v, rhs._v);
		return *this;
	}

	mint& operator/=(const mint& rhs) {
		return *this *= rhs.inv();
	}

	mint operator-() const { return mint() - *this; }

	mint pow(long long n) const {
		mint x = *this, res = 1;
		while (n) {
			if (n & 1) res *= x;
			x *= x;
			n >>= 1;
		}
		return res;
	}

	mint inv() const {
		auto eg = internal::inv_gcd(_v, mod());
		assert(eg.first == 1);
		return eg.second;
	}

	friend mint operator+(mint lhs, const mint& rhs) { return lhs += rhs; }
	friend mint operator-(mint lhs, const mint& rhs) { return lhs -= rhs; }
	friend mint operator*(mint lhs, const mint& rhs) { return lhs *= rhs; }
	friend mint operator/(mint lhs, const mint& rhs) { return lhs /= rhs; }

	friend bool operator==(const mint& lhs, const mint& rhs) { return lhs._v == rhs._v; }
	friend bool operator!=(const mint& lhs, const mint& rhs) { return lhs._v != rhs._v; }

private:
	unsigned int _v;
	static internal::barrett bt;
};
template <int id>
internal::barrett dynamic_modint<id>::bt(998244353); // default mod

using modint = dynamic_modint < -1 >;

// ------------------ Main -------------------
int main() {
	cout << "Dynamic modint with MOD = 10007:\n";
	modint::set_mod(10007);
	modint x = 1234, y = 5678;
	cout << "x + y = " << (x + y).val() << '\n';
	cout << "x - y = " << (x - y).val() << '\n';
	cout << "x * y = " << (x * y).val() << '\n';
	cout << "x / y = " << (x / y).val() << '\n';
	cout << "x^10  = " << x.pow(10).val() << '\n';

	return 0;
}
