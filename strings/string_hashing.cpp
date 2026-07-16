#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
using ll = long long;
constexpr int MOD = 1e9 + 7;

int _pow(int a, int b) {
    ll res = 1;

    while (b > 0) {
        if ((b & 1) == 1) {
            res = res * a % MOD;
        }

        a = a * a % MOD;
        b >>= 1;
    }

    return res;
}

int get_hash(string s) {
    int n = s.length();
    ll h = 0;
    for (int i = 0; i < n; i++) {
        h = (h + (s[i] - 'a' + 1) * _pow(31, n - i - 1) % MOD) % MOD;
    }

    return h;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cout << (get_hash("abc") == get_hash("bcd")) << endl;
}