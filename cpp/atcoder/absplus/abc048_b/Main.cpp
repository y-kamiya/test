#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define REP(i,n) for(int i=0, i##_len=(n); i<i##_len; ++i)
#define REPR(i,n) for(int i=n;i>=0;i--)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define ALL(x) (x).begin(),(x).end()
#define UNIQUE(v) v.erase( unique(v.begin(), v.end()), v.end() );
#define YES(n) cout << ((n) ? "YES" : "NO"  ) << endl
#define Yes(n) cout << ((n) ? "Yes" : "No"  ) << endl

ll calc(ll num, ll x) {
    if (num < 0) {
        return 0;
    }
    return num / x + 1;
}

int main() {
    ll a,b,x;
    cin >> a >> b >> x;

    cout << calc(b, x) - calc(a-1, x) << endl;

    return 0;
}





