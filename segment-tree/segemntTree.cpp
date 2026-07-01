#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define inf LLONG_MAX << 2

void buildSegemntTree(vector<int> &arr, vector<int> &segmentTree, int l, int r, int idx) {
	if (l == r) {
		segmentTree[idx] = arr[l];
		return;
	}

	int mid = l + (r - l) / 2;
	buildSegemntTree(arr, segmentTree, l, mid, 2 * idx + 1);
	buildSegemntTree(arr, segmentTree, mid + 1, r, 2 * idx + 2);
	segmentTree[idx] = segmentTree[2 * idx + 1] + segmentTree[2 * idx + 2];
}

void update(vector<int> &arr, vector<int> &segmentTree, int l, int r, int idx, int pos, int val) {
	if (l == r) {
		segmentTree[idx] = val;
		arr[pos] = val;
		return;
	}

	int mid = l + (r - l) / 2;
	if (pos <= mid) 
		update(arr, segmentTree, l, mid, 2 * idx + 1, pos, val);
	else
		update(arr, segmentTree, mid + 1, r, 2 * idx + 2, pos, val);\
	
	segmentTree[idx] = segmentTree[2 * idx + 1] + segmentTree[2 * idx + 2];
}

int query(vector<int> &segemntTree, int start, int end, int l, int r, int idx) {
	if (start <= l && r <= end)
		return segemntTree[idx];
	
	if (l > end || start > r)
		return 0;

	int mid = l + (r - l) / 2;
	int left = query(segemntTree, start, end, l, mid, 2 * idx + 1);
	int right = query(segemntTree, start, end, mid + 1, r, 2 * idx + 2);

	return left + right;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	vector<int> arr(n);
	for (auto &i : arr) {
		cin >> i;
	}

	arr.size();

	vector<int> segmentTree(4 * n);
	buildSegemntTree(arr, segmentTree, 0, n - 1, 0);
	
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

	cout << "Current Sum: " << query(segmentTree, 0, n - 1, 0, n - 1, 0) << '\n';
	update(arr, segmentTree, 0, n - 1, 0, 2, 10);
	cout << "After update:" << '\n';
	for (auto &i : segmentTree) {
		cout << i << " ";
	}
	cout << '\n';

	cout << "Sum after update: " << query(segmentTree, 0, n - 1, 0, n - 1, 0) << '\n';
}