#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'

const ll MOD = 1e9 + 7;
int dp[101][101][101];

int solve(string& w1, string& w2, string& target, int i, int j, int k) {
    if (k == target.length() && i > 0 && j > 0)
        return 1;
    
    if (dp[i][j][k] != -1)
        return dp[i][j][k];

    int ans = 0;

    // take from wrd1
    for (int p = i; p < w1.length(); p++) {
        if (w1[p] == target[k]) {
            ans = (ans + solve(w1, w2, target, i + 1, j, k + 1)) % MOD;
        }
    }

    // take from wrd2
    for (int p = i; p < w2.length(); p++) {
        if (w2[p] == target[k]) {
            ans = (ans + solve(w1, w2, target, i, j + 1, k + 1)) % MOD;
        }
    }

    return dp[i][j][k] = ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s1 = "abc", s2 = "bac", target = "abc";
    cout << "hello" << endl;
    
    memset(dp, -1, sizeof(dp));
    int ans =  solve(s1, s2, target, 0, 0, 0);

    cout << ans << endl;
}