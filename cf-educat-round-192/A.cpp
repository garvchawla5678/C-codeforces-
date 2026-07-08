#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--)
    {
        int k;
        cin >> k;
        vector<int> f(k);

        for (int i = 0; i < k; i++)
            cin >> f[i];

        int freq2 = 0, freq3 = 0;

        for (int x : f)
        {
            if (x == 2)
                freq2++;
            else if (x >= 3)
                freq3++;
        }

        cout << ((freq2 >= 2 || freq3 > 0) ? "YES" : "NO") << endl;
    }
}