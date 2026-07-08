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
        int n;
        cin >> n;
        vector<int> a(n);
        vector<int> frq(4, 0);

        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
            frq[a[i]]++;
        }

        int parts = 0;
        bool part1 = 0, part2 = 0;
        int left = 0;
        int f1 = frq[1], f2 = frq[2], f3 = frq[3];
        for (int right = 0; right < n; )
        {
            frq[a[right]]--;
            if (!part1 && (f2 - frq[2]) + (f3 - frq[3]) <= f1 - frq[1])
            {   
                while (++right < n && a[right] == 3) {
                    frq[3]--;
                    if ((f2 - frq[2]) + (f3 - frq[3]) <= f1 - frq[1]) {
                        continue;
                    }
                    else {
                        frq[3]++;
                        break;
                    }
                }
                
                parts++;
                left = right;
                part1 = 1;
                f1 = frq[1], f2 = frq[2], f3 = frq[3];
                continue;
            }
            if (part1 && !part2 && right >= left &&
                (f1 - frq[1]) + (f2 - frq[2]) >= (f3 - frq[3]))
            {
                parts++;
                part2 = 1;
                left = right + 1;
                f1 = frq[1], f2 = frq[2], f3 = frq[3];
                break;
            }
            right++;
        }
        if (parts == 2 && n - left > 0)
        {
            cout << "YES" << endl;
        }
        else
            cout << "NO" << endl;
    }

    
}