#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        arr[i] = x;
    }

    vector<vector<int>> queries(m, vector<int>(2, 0));
    for (int i = 0; i < m; i++) {
        cin >> queries[i][0] >> queries[i][1];
    }

    vector<int> prefix(n + 1);

    for (int i = 1; i < n + 1; i++) {
        prefix[i] = prefix[i - 1] + arr[i - 1];
    }

    for (auto quer : queries) {
        int l = quer[0] - 1;
        int r = quer[1] - 1;

        int ans = prefix[r + 1] - prefix[l];
        cout << ans << endl;
    }
}