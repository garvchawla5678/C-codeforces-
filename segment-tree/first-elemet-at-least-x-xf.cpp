#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long int

vector<int> segmentTree;

void buildSegmentTree(vector<int> &arr, int l, int r, int idx) {
	if (l == r) {
		segmentTree[idx] = arr[l];
		return;
	}

	int mid = l + (r - l) / 2;
	buildSegmentTree(arr, l, mid, 2 * idx + 1);
	buildSegmentTree(arr, mid + 1, r, 2 * idx + 2);
	segmentTree[idx] = max(segmentTree[2 * idx + 1], segmentTree[2 * idx + 2]);
}

void update(vector<int>& arr, int l, int r, int idx, int pos, int val) {
    if (l == r) {
        segmentTree[idx] = val;
        arr[pos] = val;
        return;
    }

    int mid = l + (r - l) / 2;
    if (mid >= pos)
        update(arr, l, mid, 2 * idx + 1, pos, val);
    else 
        update(arr, mid + 1, r, 2 * idx + 2, pos, val);

    segmentTree[idx] = max(segmentTree[2 * idx + 1], segmentTree[2 * idx + 2]);
}

int query(int l, int r, int idx, int x, int limit) {
    if (r < limit)
        return -1;

    if (segmentTree[idx] < x) {
        return -1;
    }

    if (l == r) {
        if (l >= limit) return l;
        return -1;
    }

    int mid = l + (r - l) / 2;

    int ans = query(l, mid, 2 * idx + 1, x , limit);
    if (ans != -1)
        return ans;

    return query(mid + 1, r, 2 * idx + 2, x, limit);
}

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

    vector<vector<int>> queries(m, vector<int>(3, 0));
    for (int i = 0; i < m; i++) {
        cin >> queries[i][0] >> queries[i][1] >> queries[i][2];
    }

    segmentTree.assign(4 * n, 0);
    buildSegmentTree(arr, 0, n - 1, 0);

    for (auto quer : queries) {
        int type = quer[0];
        if (type == 1) {
            update(arr, 0 , n - 1, 0, quer[1], quer[2]);
        } else {
            cout << query(0, n - 1, 0, quer[1], quer[2]) << endl;
        }
    }
}