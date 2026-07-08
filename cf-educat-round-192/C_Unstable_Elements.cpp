#include <bits/stdc++.h> 
using namespace std; 

#define endl '\n' 
#define int long long 

signed main() { 
    ios::sync_with_stdio(0); 
    cin.tie(NULL); 
    
    int t; cin >> t; 
    while(t--) { 
        int n, k; 
        cin >> n >> k; 
        
        vector<int> a(n); 
        for (auto &v:a) cin >> v; 
        vector<int> map(n + 1); 
        
        for (int i = 0; i < n; ) { 
            int j = i + 1; 
            while (j < n && a[i] == a[j]) { 
                j++; 
            } 
            map[j - i] += 1; i = j; 
        } 
        
        int sum = 0, tot = 0, ans = 0; 
        for (int sz = n; sz >= 1; sz--) { 
            if (map[sz] == 0) continue; 
            
            sum += sz * map[sz]; 
            tot += map[sz]; 
            
            int curr = sum - (sz - 1) * tot; 
            if (curr <= k && (k - curr) % tot == 0) ans += 1; 
        } 
        
        cout << ans << endl; 
    } 
}