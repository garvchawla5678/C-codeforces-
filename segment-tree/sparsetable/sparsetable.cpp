#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

struct SparseTable{
    int n, LOG;
    vector<vector<int>> table;

    int merge(int a, int b) {
        return min(a, b);
    }

    SparseTable(const vector<int>& arr) : n(size(arr)), LOG(__lg(n)), table(n, vector<int>(LOG + 1, -1)) {
        for (int j = 0; j <= LOG; j++) {
            for (int i = 0; i <= n - (1 << j); i++) {
                if (j == 0) table[i][j] = arr[i];
                else table[i][j] = merge(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int query(int l, int r) {
        int len = __lg(r - l + 1);
        return merge(table[l][len], table[r - (1 << len) + 1][len]);
    }
};

signed main() {
    vector<int> arr = {1, 3, 5, 2, 7, 1};
    SparseTable st(arr);

    cout << st.query(1, 5) << endl;
}