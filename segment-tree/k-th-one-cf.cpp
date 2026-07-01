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
	segmentTree[idx] = segmentTree[2 * idx + 1] + segmentTree[2 * idx + 2];
}

void update(vector<int>& arr, int l, int r, int idx, int pos) {
    if (l == r) {
        segmentTree[idx] = !segmentTree[idx];
        arr[l] = !arr[l];
        return;
    }

    int mid = l + (r - l) / 2;
    if (mid >= pos)
        update(arr, l, mid, 2 * idx + 1, pos);
    else 
        update(arr, mid + 1, r, 2 * idx + 2, pos);

    segmentTree[idx] = segmentTree[2 * idx + 1] + segmentTree[2 * idx + 2];
}

int query(int l, int r, int idx, int k) {
    if (segmentTree[idx] < k)
        return -1;

    if (l == r)
        return l;

    int mid = (l + r) / 2;

    if (segmentTree[2 * idx + 1] >= k)
        return query(l, mid, 2 * idx + 1, k);

    return query(mid + 1, r, 2 * idx + 2,
                 k - segmentTree[2 * idx + 1]);
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

    vector<vector<int>> queries(m, vector<int>(2, 0));
    for (int i = 0; i < m; i++) {
        cin >> queries[i][0] >> queries[i][1];
    }

    // for (auto i : arr)
    //     cout << i << ' ';
    
    // cout << endl;
    // for (auto i : queries) {
    //     cout << i[0] << ' ' << i[1] << endl;
    // }

    segmentTree.assign(4 * n, 0);
    buildSegmentTree(arr, 0, n - 1, 0);
    for (auto quer : queries) {
        int type = quer[0];
        if (type == 1) {
            update(arr, 0 , n - 1, 0, quer[1]);
        } else {
            cout << query(0, n - 1, 0, quer[1] + 1) << endl;
        }
    }
}