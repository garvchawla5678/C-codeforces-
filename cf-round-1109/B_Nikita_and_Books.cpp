#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;

    while (t--)
    {
        int n;
        cin >> n;
        if (n == 1) {
            cout << "YES" << endl;
            continue;
        }
        vector<int> a(n);

        for (auto &x : a) {
            cin >> x;
        }

        int t = a[0] - 1;
        a[1] += t;
        a[0] = 1;

        for (int i = 1; i < n; i++) {
            if (a[i] < a[i - 1] + 1) {
                cout << "NO\n";
                goto done;
            }

            int extra = a[i] - (a[i - 1] + 1);
            a[i] = a[i - 1] + 1;

            if (i + 1 < n)
                a[i + 1] += extra;
        }

        cout << "YES\n";
        done:;
    }
}