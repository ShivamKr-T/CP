#include <bits/stdc++.h>
using namespace std;

// constexpr int mod = 998244353;
constexpr int mod = 1e9 + 7;
constexpr int inf = 0x3f3f3f3f3f3f3f3f;

class ModInt {
public:
    using mint = ModInt;

    unsigned int _v;
    static int MOD;

    // Constructors
    ModInt() : _v(0) {}

    template <typename T>
    ModInt(T v) {
        long long x = v % (long long)MOD;
        if (x < 0) x += MOD;
        _v = (unsigned int)(x);
    }

    // Accessor
    unsigned int val() const { return _v; }

    // Arithmetic operators
    mint& operator+=(const mint& rhs) {
        _v += rhs._v;
        if (_v >= MOD) _v -= MOD;
        return *this;
    }

    mint& operator-=(const mint& rhs) {
        _v += MOD - rhs._v;
        if (_v >= MOD) _v -= MOD;
        return *this;
    }

    mint& operator*=(const mint& rhs) {
        _v = (unsigned int)((unsigned long long)_v * rhs._v % MOD);
        return *this;
    }

    mint& operator/=(const mint& rhs) {
        return *this *= rhs.inv();
    }

    mint operator-() const { return mint(0) - *this; }

    mint pow(long long n) const {
        mint x = *this, res = 1;
        while (n > 0) {
            if (n & 1) res *= x;
            x *= x;
            n >>= 1;
        }
        return res;
    }

    mint inv() const {
        assert(_v);
        return pow(MOD - 2);
    }

    // Stream operators
    friend istream& operator>>(istream& in, ModInt& x) {
        long long v;
        in >> v;
        x = ModInt(v);
        return in;
    }

    friend ostream& operator<<(ostream& out, const ModInt& x) {
        return out << x.val();
    }

    // Comparison operators
    friend bool operator==(const mint& lhs, const mint& rhs) { return lhs._v == rhs._v; }
    friend bool operator!=(const mint& lhs, const mint& rhs) { return lhs._v != rhs._v; }

    // Arithmetic friend operators
    friend mint operator+(mint lhs, const mint& rhs) { return lhs += rhs; }
    friend mint operator-(mint lhs, const mint& rhs) { return lhs -= rhs; }
    friend mint operator*(mint lhs, const mint& rhs) { return lhs *= rhs; }
    friend mint operator/(mint lhs, const mint& rhs) { return lhs /= rhs; }
};

// Define static modulus
int ModInt::MOD = mod;
// ------------------ Main -------------------
int main() {
        ModInt a, b; cin >> a >> b;
    
        cout << (a + b).val() << endl;
        cout << (a - b).val() << endl;
        cout << (a * b).val() << endl;
        cout << (a / b).val() << endl;
        cout << a.pow(b.val()) << endl;
        cout << a.inv() << endl;
}
