const int mod = 1e9 + 7;
const int N = 1e5 + 1;

int factorial[N], inverse_factorial[N];

long long power(int x, int y) {
    int res = 1; x %= mod;
    if (x == 0) return 0;
    while (y > 0) {
        if (y & 1) res = 1LL * res * x % mod;
        y >>= 1;
        x = 1LL * x * x % mod;
    }
    return res%mod;
}

void compute() {
    factorial[0] = 1;
    for (int i = 1; i < N; i++)
        factorial[i] = 1LL * factorial[i - 1] * i % mod;

    inverse_factorial[N - 1] = power(factorial[N - 1], mod - 2);
    for (int i = N - 2; i >= 0; i--)
        inverse_factorial[i] = 1LL * inverse_factorial[i + 1] * (i + 1) % mod;
}

int nCr(int n, int k) {
    if (k < 0 || k > n) return 0;
    return 1LL * factorial[n] * inverse_factorial[k] % mod * inverse_factorial[n - k] % mod;
}
