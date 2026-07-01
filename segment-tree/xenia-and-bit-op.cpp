#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

vector<int> st;

int merge(int a, int b, int c)
{
    if (c)
        return a | b;
    return a ^ b;
}

void buildSegmentTree(vector<int> &arr, int l, int r, int idx, int type)
{
    if (l == r)
    {
        st[idx] = arr[l];
        return;
    }

    int mid = l + (r - l) / 2;
    buildSegmentTree(arr, l, mid, 2 * idx + 1, 1 - type);
    buildSegmentTree(arr, mid + 1, r, 2 * idx + 2, 1 - type);
    st[idx] = merge(st[2 * idx + 1], st[2 * idx + 2], type);
}

void update(vector<int> &arr, int l, int r, int idx, int pos, int val, int type)
{
    if (l == r)
    {
        st[idx] = val;
        arr[pos] = val;
        return;
    }

    int mid = l + (r - l) / 2;
    if (pos <= mid)
        update(arr, l, mid, 2 * idx + 1, pos, val, 1 - type);
    else
        update(arr, mid + 1, r, 2 * idx + 2, pos, val, 1 - type);

    st[idx] = merge(st[2 * idx + 1], st[2 * idx + 2], type);
}

int query()
{
    return st[0];
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    int type = n % 2;
    n = 1 << n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        arr[i] = x;
    }

    vector<vector<int>> queries(m, vector<int>(2, 0));
    for (int i = 0; i < m; i++)
    {
        cin >> queries[i][0] >> queries[i][1];
    }

    st.resize(2 * n - 1);
    buildSegmentTree(arr, 0, n - 1, 0, type);

    for (auto quer : queries)
    {
        int pos = quer[0] - 1;
        int val = quer[1];

        update(arr, 0, n - 1, 0, pos, val, type);

        cout << query() << endl;
    }
}