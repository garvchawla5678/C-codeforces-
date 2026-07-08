#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define ll long long

int search(vector<int>& arr, int i, int d) {
    int l = i;
    int r = arr.size();

    while (r - l > 1) {
        int mid = (l + r) / 2;
        (arr[mid] - arr[i] <= d) ? l = mid : r = mid;
    }

    return l;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);

    int n, d;
    cin >> n >> d;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) 
    {
        int x; cin >> x;
        arr[i] = x;
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
       int right = search(arr, i, d);
       
       int len = right - i;
       if (len >= 2) ans += 1LL * len * (len - 1) / 2;
    }

    cout << ans << endl;
}
