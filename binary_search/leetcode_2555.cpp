#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

int upper(vector<int>& p, int target, int n, unordered_map<int, int> mp) {
    if (mp.find(target) != mp.end())
        return mp[target];

    int l = -1, r = n;

    while(r - l > 1) {
        int mid = (l + r) / 2;
        (p[mid] < target + 1) ? l = mid : r = mid;
    }

    return mp[target] = l;
}

int maximizeWin(vector<int>& pos, int k) {
    int n = pos.size();
    vector<int> ans(n, 0);
    unordered_map<int, int> mp;

    for (int i = 0; i < n; i++) {
        int idx = upper(pos, pos[i] + k, n, mp);
        int ele = idx - i + 1;
        ans[i] = ele;
    }

    vector<int> suffix(n + 1, 0);
    for (int i = n - 1; i >= 0; i--) {
        suffix[i] = max(suffix[i + 1], ans[i]);
    }

    int res = 0;
    for (int i = 0; i < n; i++) {
        int tmp = ans[i] + suffix[i + ans[i]];
        res = max(tmp, res);
    }

    return res;
}

int main()
{
    vector<int> arr = {1, 1, 2, 2, 3, 3, 5};
    int k = 2;

    int ans = maximizeWin(arr, k);
    // cout << endl;
    cout << ans << endl;
}