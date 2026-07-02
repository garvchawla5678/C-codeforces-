#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

vector<int> st, lazy;

int merge(int a, int b)
{
    return (a & b);
}

void buildSegmentTree(vector<int> &arr, int l, int r, int idx)
{
    if (l == r)
    {
        st[idx] = arr[l];
        return;
    }

    int mid = l + (r - l) / 2;

    buildSegmentTree(arr, l, mid, 2 * idx + 1);
    buildSegmentTree(arr, mid + 1, r, 2 * idx + 2);
    st[idx] = merge(st[2 * idx + 1], st[2 * idx + 2]);
}

void propagate(int l, int r, int idx)
{
    if (l == r)
    {
        lazy[idx] = 0;
        return;
    }

    lazy[2 * idx + 1] = lazy[2 * idx + 1] | lazy[idx];
    lazy[2 * idx + 2] = lazy[2 * idx + 2] | lazy[idx];
    lazy[idx] = 0;
}

void update(int start, int end, int l, int r, int idx, int val)
{
    if (lazy[idx] != 0)
    {
        st[idx] = st[idx] | lazy[idx];
        propagate(l, r, idx);
    }

    if (start <= l && r <= end)
    {
        st[idx] = st[idx] | val;
        lazy[idx] = lazy[idx] | val;
        propagate(l, r, idx);
        return;
    }

    if (l > end || start > r)
        return;

    int mid = l + (r - l) / 2;

    update(start, end, l, mid, 2 * idx + 1, val);
    update(start, end, mid + 1, r, 2 * idx + 2, val);
    st[idx] = merge(st[2 * idx + 1], st[2 * idx + 2]);
}

int query(int start, int end, int l, int r, int idx)
{
    if (lazy[idx] != 0)
    {
        st[idx] = st[idx] | lazy[idx];
        propagate(l, r, idx);
    }

    if (start <= l && r <= end)
        return st[idx];

    if (l > end || start > r)
        return LLONG_MAX;

    int mid = l + (r - l) / 2;
    int left = query(start, end, l, mid, 2 * idx + 1);
    int right = query(start, end, mid + 1, r, 2 * idx + 2);

    return merge(left, right);
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<int> arr;
    arr.resize(n, 0);

    vector<vector<int>> queries(m, vector<int>(4, 0));
    for (int i = 0; i < m; i++)
    {
        cin >> queries[i][0];
        if (queries[i][0] == 1)
            cin >> queries[i][1] >> queries[i][2] >> queries[i][3];
        else
            cin >> queries[i][1] >> queries[i][2];
    }

    st.resize(4 * n, -1);
    lazy.resize(4 * n, 0);

    buildSegmentTree(arr, 0, n - 1, 0);

    for (auto quer : queries)
    {
        int type = quer[0];

        if (type == 1)
        {
            int l = quer[1];
            int r = quer[2] - 1;
            int val = quer[3];

            update(l, r, 0, n - 1, 0, val);
        }
        else
        {
            int l = quer[1];
            int r = quer[2] - 1;

            cout << query(l, r, 0, n - 1, 0) << endl;
        }
    }
}