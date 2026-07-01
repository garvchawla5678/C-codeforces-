#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

struct Node{
    int ans;
    int open;
    int close;

    Node (int a, int b, int c) {
        ans = a;
        open = b;
        close = c;
    }
};

vector<Node> st;

Node merge(Node a, Node b) {
    int combineVal = min(a.open, b.close);
    return Node(a.ans + b.ans + combineVal, a.open + b.open - combineVal, a.close + b.close - combineVal);
}

void buildSegmentTree(vector<char>& arr, int l, int r, int idx) {
    if (l == r) {
        st[idx].open = (arr[l] == '(');
        st[idx].close = (arr[l] == ')');
        return;
    }

    int mid = l + (r - l) / 2;
    buildSegmentTree(arr, l, mid, 2 * idx + 1);
    buildSegmentTree(arr, mid + 1, r, 2 * idx + 2);
    st[idx] = merge(st[2 * idx + 1], st[2 * idx + 2]);
}

Node query(int start, int end, int l, int r, int idx) {
    if (start > r || l > end)
        return Node(0, 0, 0);
    
    if (start <= l && r <= end) 
        return st[idx];
    
    int mid = l + (r - l) / 2;
    Node left = query(start, end, l, mid, 2 * idx + 1);
    Node right = query(start, end, mid + 1, r, 2 * idx + 2);

    return merge(left, right);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s; int m;
    cin >> s >> m;
    int n = s.length();

    vector<vector<int>> queries(m, vector<int>(2, 0));
    for (int i = 0; i < m; i++)
    {
        cin >> queries[i][0] >> queries[i][1];
    }

    vector<char> arr(n);
    int i = 0;
    for (auto ch : s) {
        arr[i++] = ch;
    }

    st.resize(4 * n, Node(0, 0, 0));
    buildSegmentTree(arr, 0, n - 1, 0);

    for (auto quer : queries) {
        int l = quer[0] - 1;
        int r = quer[1] - 1;

        cout << 2 * query(l , r, 0, n - 1, 0).ans << endl;
    } 
}