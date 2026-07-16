#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;

    while (t--)
    {
        int n;
        string s;
        cin >> n >> s;

        int x = 0, y = 0;
        for (char z : s) {
            if (z == '#') {
                y++;
                x = max(x, y);
            } else {
                y = 0;
            }
        }

        cout << (x + 1) / 2 << endl;
    }
}