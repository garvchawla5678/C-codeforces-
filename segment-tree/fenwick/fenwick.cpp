#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

vector<int> bit;

// bit[i] stores sum(a[f(i) + 1 to i])
// wehre f(i) is i but last set bit is off which is done by f(i) = i - (i & -i)

void update(int pos, int val, int n) {
    int i = pos;
    while (i <= n) {
        bit[i] += val;
        i += (i & -i);
    }
}

void buildFenwickTree(vector<int>& arr, int n) {
    bit.resize(n + 1, 0);

    for (int i = 0; i < n; i++) {
        update(i + 1, arr[i], n);
    }
}

int sum(int idx) {
    int res = 0;
    while(idx != 0) {
        res += bit[idx];
        idx -= (idx & -idx);
    }

    return res;
}

int query(int l, int r) {
    return sum(r + 1) - sum(l);
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        arr[i] = x;
    }

    vector<vector<int>> queries(m, vector<int>(3, 0));
    for (int i = 0; i < m; i++)
    {
        cin >> queries[i][0];
        if (queries[i][0] == 1)
            cin >> queries[i][1] >> queries[i][2];
        else
            cin >> queries[i][1] >> queries[i][2];
    }

    buildFenwickTree(arr, n);

    for (auto quer : queries)
    {
        int type = quer[0];

        if (type == 1)
        {
            int pos = quer[1];
            int val = quer[2];

            update(pos, val, n);
        }
        else
        {
            int l = quer[1];
            int r = quer[2];

            cout << query(l, r) << endl;
        }
    }
}