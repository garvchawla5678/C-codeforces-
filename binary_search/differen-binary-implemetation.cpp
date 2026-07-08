#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define ll long long

int search1(vector<int>& arr, int n, int target) {
    // here we should first find where should '=' should come in "if" statement
    // then in that statement left/right = mid will come bcz that might be the naswer we are looking for
    // now we have to lean towards the changable side in mid bcz if not then we can stuck in inf loop
    // so for example here right is hcangabel side so in mid we have lean towards right by adding 1 i.e. ceiling
    int left = 0;
    int right = n - 1;

    while (left < right) {
        int mid = (left + right + 1) / 2;

        if (arr[mid] <= target) left = mid;
        if (arr[mid] > target) right = mid - 1;
    }

    return left;
}

int search2(vector<int>& arr, int n, int target) {
    // here there is no tesnion about inf loop and where to put '=' to symbol 
    // bcz here we are sinmply storing the ans in a variale
    // this is the siompler version of search1

    int left = 0;
    int right = n - 1;
    int ans = 0;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (arr[mid] == target) {
            ans = mid;
            left = mid + 1;
            continue;
        }

        if (arr[mid] < target) 
            left = mid + 1;

        if (arr[mid] > target)
            right = mid - 1;
    }

    return ans;
}

int search3(vector<int>& arr, int n, int target) {
    // uptill now we were doing [l, r] but here we are doing (l, r) means not including l and r
    // here we have to find such predicate which will form the array in following way
    // T T T T T T T F F F 
    // here we are trying to find TF junction, and are l = will T aadn r will be F
    // so let's say the ans is at idx k, then we can either form pred such that T is at k and F is at k + 1 or T is at k - 1 and F is at T

    int l = -1;
    int r = n;

    while (r - l > 1) {  // here r - l > 1 ensures that there is atleast there is one element we are looking at 
        int mid = (l + r) / 2;

        (arr[mid] < target + 1) ? l = mid : r = mid;
    }

    return l;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);

    int n, target;
    cin >> n >> target;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) 
    {
        int x; cin >> x;
        arr[i] = x;
    }

    // 1st implementation which involve ciel and floor logic
    // search1 is for finding the last occurence of the target in array
    int ans1 = search1(arr, n, target);
    cout << ans1 << endl;

    int ans2 = search2(arr, n, target);
    cout << ans2 << endl;

    int ans3 = search3(arr, n, target);
    cout << ans3 << endl;
}