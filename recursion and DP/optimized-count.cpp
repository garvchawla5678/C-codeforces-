#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'

const ll MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s1 = "abc", s2 = "bac", target = "abc";
    cout << "hello" << endl;
    
    int n1 = s1.length(), n2 = s2.length(), m = target.length();

    vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));
    dp[0][0] = 1;

    for (int k = 0; k < m; k++) {
        char c = target[k];
        vector<vector<int>> nxt(n1 + 1, vector<int>(n2 + 1, 0));

        //rowPrefix -> for every idx b in word2, we are accumualting over [0..n1] in word1
        vector<vector<int>> rowPrefix(n2 + 1, vector<int>(n1 + 1, 0));
        for (int b = 0; b <= n2; b++) {
            ll s = 0;
            for (int a = 0; a <= n1; a++) {
                s = (s + dp[a][b]) % MOD;
                rowPrefix[b][a] = s;
            }
        }

        //colPrefix -> for every idx a in word1, we are accumualting over [0..n2] in word2
        vector<vector<int>> colPrefix(n1 + 1, vector<int>(n2 + 1, 0));
        for (int a = 0; a <= n1; a++) {
            ll s = 0;
            for (int b = 0; b <= n2; b++) {
                s = (s + dp[a][b]) % MOD;
                colPrefix[a][b] = s;
            }
        }

        for (int i = 0; i < n1; i++) {
            if (s1[i] == c) {
                for (int b = 0; b <= n2; b++) {
                    nxt[i + 1][b] = (nxt[i + 1][b] + rowPrefix[b][i]) % MOD;
                }
            }
        }

        for (int j = 0; j <= n2; j++) {
            if (s2[j] == c) {
                for (int a = 0; a <= n1; a++) {
                    nxt[a][j + 1] = (nxt[a][j + 1] + colPrefix[a][j]) % MOD;
                }
            }
        }

        dp = move(nxt);
    }

    ll ans = 0;
    for (int a = 1; a <= n1; a++) {
        for (int b = 1; b <= n2; b++) {
            ans = (ans + dp[a][b]) % MOD;
        }
    }

    cout << (int) ans << endl;
}