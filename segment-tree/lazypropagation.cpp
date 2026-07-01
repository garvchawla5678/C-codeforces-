#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define inf LLONG_MAX - 1
#define int long long int

// here we are building segemnt tree for queryuing min value in a range and 
// when it times to update we have to add the value to range elements

vector<int> segmentTree, lazy;

int merge(int a, int b) {
    return min(a, b);
}

void buildSegmentTree(vector<int>& arr, int l, int r, int idx) {
    if (l == r) {
        segmentTree[idx] = arr[l];
        return;
    }

    int mid = l + (r - l) / 2;

    buildSegmentTree(arr, l, mid, 2 * idx + 1);
    buildSegmentTree(arr, mid + 1, r, 2 * idx + 2);
    segmentTree[idx] = merge(segmentTree[2 * idx + 1], segmentTree[2 * idx + 2]);
}

void propagate(int l, int r, int idx) {
    if (l == r) {
        lazy[idx] = 0;
        return;
    } 
    
    lazy[2 * idx + 1] += lazy[idx];
    lazy[2 * idx + 2] += lazy[idx];
    lazy[idx] = 0;
}

void update(int start, int end, int l, int r, int idx, int val) {
    if (lazy[idx] != 0) {
        segmentTree[idx] += lazy[idx];
        propagate(l, r, idx);
    }

    if (start <= l && r <= end) {
        segmentTree[idx] += val;
        lazy[idx] += val;
        propagate(l, r, idx);
        return;
    }

    if (l > end || start > r)
		return;
    
    int mid = l + (r - l) / 2;

    update(start, end, l, mid, 2 * idx + 1, val);
    update(start, end, mid + 1, r, 2 * idx + 2, val);
    segmentTree[idx] = merge(segmentTree[2 * idx + 1], segmentTree[2 * idx + 2]);
}

int query(int start, int end, int l, int r, int idx) {
    if (lazy[idx] != 0) {
        segmentTree[idx] += lazy[idx];
        propagate(l, r, idx);
    }

    if (start <= l && r <= end)
		return segmentTree[idx];
	
	if (l > end || start > r)
		return inf;

	int mid = l + (r - l) / 2;
	int left = query(start, end, l, mid, 2 * idx + 1);
	int right = query(start, end, mid + 1, r, 2 * idx + 2);

	return merge(left, right);
}

signed main() {
    ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	vector<int> arr(n);
	for (auto &i : arr) {
		cin >> i;
	}

    segmentTree.resize(4 * n, -1);
    lazy.resize(4 * n, 0);

    buildSegmentTree(arr, 0, n - 1, 0);

    cout << "Original array:" << '\n';
	for (auto &i : arr) {
		cout << i << " ";
	}

	cout << '\n';
	cout << '\n';

	cout << "Segment tree:" << '\n';
	for (auto &i : segmentTree) {
		cout << i << " ";
	}

    cout << endl;

    cout << "Current min: " << query(0, n - 1, 0, n - 1, 0) << endl;
    update(0, 2, 0, n - 1, 0, -5);
    cout << "Min after update: " << query(0, n - 1, 0, n - 1, 0) << endl;
}