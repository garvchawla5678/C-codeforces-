#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define double double long

int main() {
    double c;
    cin >> c;

    double l = 0;
    double r = 1e5 + 1;
    int itr = 37;

    for (int i = 0; i < itr + 13; i++) {
        double mid = (l + r) / 2;
        (mid * mid + sqrt(mid) <= c) ? l = mid : r = mid;
    }

    cout << fixed << setprecision(15);
    cout << l << endl;
}