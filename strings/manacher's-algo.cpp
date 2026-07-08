#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'

struct manacher{
    vector<int> p;

    void build(const string& s) {
        string t = "#";
        for (char c : s) {
            t += c;
            t += '#';
        }

        int n = t.length();
        p.assign(n, 0);
        int l = 0, r = 0;

        for (int i = 0; i < n; i++) {
            if (i < r) {
                p[i] = min(r - i, p[l + r - i]);
            }

            while (i - p[i] - 1 >= 0 && i + p[i] + 1 < n && t[i - p[i] - 1] == t[i + p[i] + 1]) {
                p[i]++;
            }

            if (i + p[i] > r) {
                l = i - p[i];
                r = i + p[i];
            }
        }
    }

    manacher(const string& s) {
        build(s);
    }

    int getLongest(int center, int odd) {
        int idx = 2 * center + 1 + (!odd);
        return p[idx];
    }

    bool checkPalin(int l, int r) {
        return (r - l + 1) <= getLongest((l + r) / 2, l % 2 == r % 2);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);

    string s;
    cin >> s;

    manacher ans(s);

    return 0;
}