// comput prime factors of number n [p1^e1 * p2^e2 * ..........]
auto primeFactors = [&](int n)->vector<int> {
    vector<int> result;
    while (n % 2 == 0) {
        result.push_back(2);
        n = n / 2;
    }

    for (int i = 3; i * i <= n; i = i + 2) {
        while (n % i == 0) {
            result.push_back(i);
            n = n / i;
        }
    }
    if (n > 2) result.pb(n);
    return result;
};
