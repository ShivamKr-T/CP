#include <bits/stdc++.h>
using namespace std;

namespace internal {
template <class T> using is_signed_int_t = enable_if_t<is_signed<T>::value>;
template <class T> using is_unsigned_int_t = enable_if_t<is_unsigned<T>::value>;

template <typename T>
T safe_mod(T x, T m) {
    x %= m;
    if (x < 0) x += m;
    return x;
}

struct barrett {
    unsigned int m;
    unsigned long long im;
    explicit barrett(unsigned int m) : m(m), im((unsigned long long)(-1) / m + 1) {}
    unsigned int umod() const { return m; }
    unsigned int mul(unsigned int a, unsigned int b) const {
        unsigned long long z = a; z *= b;
        unsigned long long x = ((unsigned __int128)z * im) >> 64;
        unsigned int v = (unsigned int)(z - x * m);
        return v >= m ? v - m : v;
    }
};

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
}

// ---------------- DynamicModInt Class ----------------
class DynamicModInt {
public:
    using mint = DynamicModInt;

    unsigned int _v;
    static internal::barrett bt;

    // Constructors
    DynamicModInt() : _v(0) {}

    template <typename T, internal::is_signed_int_t<T>* = nullptr>
    DynamicModInt(T v) {
        long long x = v % (long long)mod();
        if (x < 0) x += mod();
        _v = (unsigned int)x;
    }

    template <typename T, internal::is_unsigned_int_t<T>* = nullptr>
    DynamicModInt(T v) {
        _v = (unsigned int)(v % mod());
    }

    // Set modulus
    static void set_mod(int m) { bt = internal::barrett(m); }

    // Current modulus
    static int mod() { return bt.umod(); }

    // Accessor
    unsigned int val() const { return _v; }

    // Arithmetic
    mint& operator+=(const mint& rhs) { _v += rhs._v; if (_v >= mod()) _v -= mod(); return *this; }
    mint& operator-=(const mint& rhs) { _v += mod() - rhs._v; if (_v >= mod()) _v -= mod(); return *this; }
    mint& operator*=(const mint& rhs) { _v = bt.mul(_v, rhs._v); return *this; }
    mint& operator/=(const mint& rhs) { return *this *= rhs.inv(); }
    mint operator-() const { return mint(0) - *this; }

    // Exponentiation
    mint pow(long long n) const {
        mint x = *this, res = 1;
        while (n) { if (n & 1) res *= x; x *= x; n >>= 1; }
        return res;
    }

    // Modular inverse
    mint inv() const {
        auto eg = internal::inv_gcd(_v, mod());
        assert(eg.first == 1);
        return eg.second;
    }

    // Stream operators
    friend istream& operator>>(istream& in, mint& x) {
        long long v; in >> v;
        x = mint(v);
        return in;
    }

    friend ostream& operator<<(ostream& out, const mint& x) {
        return out << x.val();
    }

    // Comparison
    friend bool operator==(const mint& lhs, const mint& rhs) { return lhs._v == rhs._v; }
    friend bool operator!=(const mint& lhs, const mint& rhs) { return lhs._v != rhs._v; }

    // Friend arithmetic
    friend mint operator+(mint lhs, const mint& rhs) { return lhs += rhs; }
    friend mint operator-(mint lhs, const mint& rhs) { return lhs -= rhs; }
    friend mint operator*(mint lhs, const mint& rhs) { return lhs *= rhs; }
    friend mint operator/(mint lhs, const mint& rhs) { return lhs /= rhs; }
};

// Default modulus
internal::barrett DynamicModInt::bt(998244353);  // always constant
// Can set modulus dynamically :- DynamicModInt::set_mod(1000000007);

// ------------------ Main -------------------
int main() {
	DynamicModInt a, b; cin >> a >> b;
	cout << a + b << endl;
	cout << a * b << endl;
	DynamicModInt::set_mod(1000000007);
	cout << a.pow(b.val()) << endl;
}
