#include<bits/stdc++.h>
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

// ------------------ Static Modint -------------------
template<int m>
using enable_if_mod = enable_if_t < (1 <= m) >;

template <int m, enable_if_mod<m>* = nullptr>
struct static_modint : internal::static_modint_base {
    using mint = static_modint;

    static constexpr int mod() { return m; }
    static mint raw(int v) { mint x; x._v = v; return x; }

    static_modint() : _v(0) {}

    template <class T, internal::is_signed_int_t<T>* = nullptr>
    static_modint(T v) {
        long long x = v % (long long)(m);
        if (x < 0) x += m;
        _v = (unsigned int)(x);
    }

    template <class T, internal::is_unsigned_int_t<T>* = nullptr>
    static_modint(T v) {
        _v = (unsigned int)(v % m);
    }

    unsigned int val() const { return _v; }

    mint& operator+=(const mint& rhs) {
        _v += rhs._v;
        if (_v >= m) _v -= m;
        return *this;
    }
    mint& operator-=(const mint& rhs) {
        _v += m - rhs._v;
        if (_v >= m) _v -= m;
        return *this;
    }
    mint& operator*=(const mint& rhs) {
        _v = (unsigned int)((unsigned long long)_v * rhs._v % m);
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
        assert(_v);
        return pow(m - 2);
    }

    friend mint operator+(mint lhs, const mint& rhs) { return lhs += rhs; }
    friend mint operator-(mint lhs, const mint& rhs) { return lhs -= rhs; }
    friend mint operator*(mint lhs, const mint& rhs) { return lhs *= rhs; }
    friend mint operator/(mint lhs, const mint& rhs) { return lhs /= rhs; }

    friend bool operator==(const mint& lhs, const mint& rhs) { return lhs._v == rhs._v; }
    friend bool operator!=(const mint& lhs, const mint& rhs) { return lhs._v != rhs._v; }

private:
    unsigned int _v;
};

using modint998244353 = static_modint<998244353>;
using modint1000000007 = static_modint<1000000007>;


using mint = modint1000000007;

struct Sieve {
    vector<bool> isPrime;          // For basic primality testing
    vector<int> min_factor;        // For linear sieve factorization
    vector<int> primes;            // List of prime numbers
    int n;


    // Linear sieve algorithm for fast prime factorization
    // Complexity: O(N) time, O(N) space:
    // - MAXN = 10^7:  ~44 MB,  80~100 ms (Codeforces / AtCoder GCC, C++17)
    // - MAXN = 10^8: ~435 MB, 810~980 ms (Codeforces / AtCoder GCC, C++17)
    // - https://cp-algorithms.com/algebra/prime-sieve-linear.html
    explicit Sieve(int MAXN) : n(MAXN), min_factor(MAXN + 1), isPrime(MAXN + 1, true) {
        isPrime[0] = isPrime[1] = false;

        // Linear sieve for min_factor and primes
        for (int d = 2; d <= MAXN; d++) {
            if (!min_factor[d]) {
                min_factor[d] = d;
                primes.emplace_back(d);
                isPrime[d] = true;
            }
            for (const auto &p : primes) {
                if (p > min_factor[d] || 1LL * d * p > MAXN) break;
                min_factor[d * p] = p;
                isPrime[d * p] = false;
            }
        }
    }

    // Check if a number is prime
    bool is_prime(int num) const {
        if (num <= n) return isPrime[num];
        for (int p : primes) {
            if (1LL * p * p > num) break;
            if (num % p == 0) return false;
        }
        return num > 1;
    }

    // Get all prime numbers up to n
    vector<int> get_primes() const {
        return primes;
    }

    // Prime factorization for 1 <= x <= MAXN^2
    // Complexity: O(log x)           (x <= MAXN)
    //             O(MAXN / log MAXN) (MAXN < x <= MAXN^2)
    template <class T> map<T, int> prime_factors(T x) const {
        map<T, int> ret;
        assert(x > 0 && x <= 1LL * (n - 1) * (n - 1));
        for (const auto &p : primes) {
            if (x < T(n)) break;
            while (!(x % p)) x /= p, ret[p]++;
        }
        if (x >= T(n)) ret[x]++, x = 1;
        while (x > 1) ret[min_factor[x]]++, x /= min_factor[x];
        return ret;
    }

    // Get count of primes up to n
    int count_primes() const {
        return primes.size();
    }

    // Get nth prime number (1-based index)
    int nth_prime(int index) const {
        if (index < 1 || index > primes.size()) return -1;
        return primes[index - 1];
    }

    // Get next prime after a number
    int next_prime(int num) const {
        if (num < 2) return 2;
        for (int i = num + 1; i <= n; i++) {
            if (isPrime[i]) return i;
        }
        int next = num + 1;
        while (!is_prime(next)) next++;
        return next;
    }

    // Get previous prime before a number
    int prev_prime(int num) const {
        if (num <= 2) return -1;
        for (int i = num - 1; i >= 2; i--) {
            if (isPrime[i]) return i;
        }
        return -1;
    }

    // Enumerate divisors of 1 <= x <= MAXN^2
    // Be careful of highly composite numbers https://oeis.org/A002182/list
    // https://gist.github.com/dario2994/fb4713f252ca86c1254d#file-list-txt (n, (# of div. of n)):
    template <class T> vector<T> divisors(T x) const {
        vector<T> ret{1};
        for (const auto p : prime_factors(x)) {
            int n = ret.size();
            for (int i = 0; i < n; i++) {
                for (T a = 1, d = 1; d <= p.second; d++) {
                    a *= p.first;
                    ret.push_back(ret[i] * a);
                }
            }
        }
        return ret; // NOT sorted
    }

    // Euler phi functions of divisors of x -> [x, φ(x)]
    // Complexity: O(sqrt(x) + d(x))
    template <class T> map<T, T> euler_of_divisors(T x) const {
        assert(x >= 1);
        map<T, T> ret;
        ret[1] = 1;
        vector<T> divs{1};
        for (auto p : prime_factors(x)) {
            int n = ret.size();
            for (int i = 0; i < n; i++) {
                ret[divs[i] * p.first] = ret[divs[i]] * (p.first - 1);
                divs.push_back(divs[i] * p.first);
                for (T a = divs[i] * p.first, d = 1; d < p.second; a *= p.first, d++) {
                    ret[a * p.first] = ret[a] * p.first;
                    divs.push_back(a * p.first);
                }
            }
        }
        return ret;
    }

    // Moebius function table
    vector<int> GenerateMoebiusFunctionTable() const {
        vector<int> ret(n + 1);
        for (unsigned i = 1; i <= n; i++) {
            if (i == 1) {
                ret[i] = 1;
            } else if ((i / min_factor[i]) % min_factor[i] == 0) {
                ret[i] = 0;
            } else {
                ret[i] = -ret[i / min_factor[i]];
            }
        }
        return ret;
    }

    // Calculate kth powers up to nmax
    template <class MODINT> vector<MODINT> enumerate_kth_pows(long long K, int nmax) const {
        assert(nmax <= n);
        assert(K >= 0);
        if (K == 0) return vector<MODINT>(nmax + 1, 1);
        vector<MODINT> ret(nmax + 1);
        ret[0] = 0, ret[1] = 1;
        for (int i = 2; i <= nmax; i++) {
            if (min_factor[i] == i) {
                ret[i] = MODINT(i).pow(K);
            } else {
                ret[i] = ret[i / min_factor[i]] * ret[min_factor[i]];
            }
        }
        return ret;
    }
}; Sieve sieve(20);



int main() {
    cout << sieve.is_prime(17) << "\n"; // 1 (true)\

    auto factors = sieve.prime_factors(12); // {2: 2, 3: 1}
    for (auto &[x, y] : factors) cout << x << " " << y << "\n";

    auto divs = sieve.divisors(12); // {1, 2, 4, 3, 6, 12}
    for (auto &x : divs) cout << x << " ";
    cout << "\n";

    auto euler = sieve.euler_of_divisors(12); // {1: 1, 2: 1, 3: 2, 4: 2, 6: 2, 12: 4}
    for (auto &[x, y] : euler) cout << x << " " << y << "\n";

    auto moebius = sieve.GenerateMoebiusFunctionTable(); // [0, 1, -1, -1, 0, ...]
    for (auto &x : moebius) cout << x << " ";
    cout << "\n";


    auto pow_k = sieve.enumerate_kth_pows<mint>(5, 20);
    for (auto &x : pow_k) cout << x.val() << " ";
    cout << "\n";
}
