#include <bits/stdc++.h>
using namespace std;

class FenwickTree {
private:
    vector<int> fen;
    int n;

public:
    explicit FenwickTree(int n) : n(n), fen(n + 1, 0) {}
    
    void update(int i, int val)
    {
        if(i<1 or i>n) return;
        for(;i<=n;i+=(i&(-i))) fen[i]+=val;
    }

    int query(int i) {
        int res=0;
        for(;i>=1;i-=(i&(-i))) res+=fen[i];
        return res;
    }

    int query(int l, int r) { return query(r)-query(l-1); }
};

int main() {
    vector<int> arr = {2, 4, 1, 7, 3};
    int n = arr.size();

    FenwickTree bit(n);

    // Build the tree from the original array
    for (int i = 1; i <= n; i++) {
        bit.update(i, arr[i - 1]);
    }

    cout << bit.query(3) << '\n';       // 7
    cout << bit.query(2, 4) << '\n';    // 12

    bit.update(3, 5);  // Add 5 to position 3

    cout << bit.query(3) << '\n';       // 12
    cout << bit.query(2, 4) << '\n';    // 17

    return 0;
}