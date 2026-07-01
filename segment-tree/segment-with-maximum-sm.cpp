#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

struct Node
{
    int sum;
    int prefix;
    int suffix;
    int mx;
};

vector<Node> segmentTree;

void buildSegmentTree(vector<int> &arr, int l, int r, int idx)
{
    if (l == r)
    {
        segmentTree[idx].sum = arr[l];
        segmentTree[idx].prefix = max(0LL, arr[l]);
        segmentTree[idx].suffix = max(0LL, arr[l]);
        segmentTree[idx].mx = max(0LL, arr[l]);
        return;
    }

    int mid = l + (r - l) / 2;
    buildSegmentTree(arr, l, mid, 2 * idx + 1);
    buildSegmentTree(arr, mid + 1, r, 2 * idx + 2);
    segmentTree[idx].prefix = max(segmentTree[2 * idx + 1].prefix, segmentTree[2 * idx + 1].sum + segmentTree[2 * idx + 2].prefix);
    segmentTree[idx].suffix = max(segmentTree[2 * idx + 2].suffix, segmentTree[2 * idx + 2].sum + segmentTree[2 * idx + 1].suffix);
    segmentTree[idx].sum = segmentTree[2 * idx + 1].sum + segmentTree[2 * idx + 2].sum;
    segmentTree[idx].mx = max({segmentTree[2 * idx + 1].mx, segmentTree[2 * idx + 2].mx, segmentTree[2 * idx + 1].suffix + segmentTree[2 * idx + 2].prefix});
}

void update(vector<int> &arr, int l, int r, int idx, int pos, int val)
{
    if (l == r)
    {
        segmentTree[idx].sum = val;
        segmentTree[idx].prefix = max(0LL, val);
        segmentTree[idx].suffix = max(0LL, val);
        segmentTree[idx].mx = max(0LL, val);
        arr[pos] = val;
        return;
    }

    int mid = l + (r - l) / 2;
    if (mid >= pos)
        update(arr, l, mid, 2 * idx + 1, pos, val);
    else
        update(arr, mid + 1, r, 2 * idx + 2, pos, val);

    segmentTree[idx].prefix = max(segmentTree[2 * idx + 1].prefix, segmentTree[2 * idx + 1].sum + segmentTree[2 * idx + 2].prefix);
    segmentTree[idx].suffix = max(segmentTree[2 * idx + 2].suffix, segmentTree[2 * idx + 2].sum + segmentTree[2 * idx + 1].suffix);
    segmentTree[idx].sum = segmentTree[2 * idx + 1].sum + segmentTree[2 * idx + 2].sum;
    segmentTree[idx].mx = max({segmentTree[2 * idx + 1].mx, segmentTree[2 * idx + 2].mx, segmentTree[2 * idx + 1].suffix + segmentTree[2 * idx + 2].prefix});
}

int query()
{
    return segmentTree[0].mx;
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

    vector<vector<int>> queries(m, vector<int>(2, 0));
    for (int i = 0; i < m; i++)
    {
        cin >> queries[i][0] >> queries[i][1];
    }

    Node neutral = {0, 0, 0, 0};
    segmentTree.assign(4 * n, neutral);

    buildSegmentTree(arr, 0, n - 1, 0);

    cout << query() << endl;

    for (auto quer : queries)
    {
        int idx = quer[0];
        int val = quer[1];

        update(arr, 0, n - 1, 0, idx, val);
        cout << query() << endl;
    }
}