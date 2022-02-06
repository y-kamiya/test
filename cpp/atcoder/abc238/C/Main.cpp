#include <bits/stdc++.h>
#include <string>
using namespace std;

using ll = long long;

#define REP(i,n) for(int i=0, i##_len=(n); i<i##_len; ++i)
#define REPR(i,n) for(int i=n;i>=0;i--)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define FORR(i,a,b) for(int i=(a);i>=(b);--i)
#define ALL(x) (x).begin(),(x).end()
#define UNIQUE(v) v.erase( unique(v.begin(), v.end()), v.end() );
#define YES(n) cout << ((n) ? "YES" : "NO"  ) << endl
#define Yes(n) cout << ((n) ? "Yes" : "No"  ) << endl
#define PRINT_DOUBLE(n, x) cout << std::fixed << std::setprecision(n) << x << endl;

static const ll MOD = 998244353;


ll N;

ll sum(ll maxValue) {
    // cout << maxValue << endl;
    ll a = 0;
    if (maxValue % 2 == 0) {
        a = ((maxValue / 2) % MOD) * ((maxValue + 1) % MOD);
    } else {
        a = (maxValue % MOD) * (((maxValue + 1) / 2) % MOD);
    }
    return a;
}

ll sumDigit(int digit) {
    ll maxValue = 9 * pow(10, digit);
    return sum(maxValue);
}

void _main() {
    cin >> N;

    string s = to_string(N);
    int digit = s.size();

    // cout << digit << endl;

    ll ans = 0;
    REP(i, digit-1) {
        ll a = sumDigit(i) % MOD;
        // cout << i << ": " << a << endl;
        ans = (ans + a) % MOD;
    }
    ll c = (N - (ll)pow(10, digit-1)) + 1;
    // cout << "c: " << c << " " << N << endl;
    ll b = sum(c) % MOD;
    // cout << "max: " << b << endl;
    ans = (ans + b) % MOD;

    cout << ans << endl;
}

int main() {
    _main();
    return 0;
}

// WC 21:57
// AC 22:15
