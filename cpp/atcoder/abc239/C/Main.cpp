#include <bits/stdc++.h>
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


ll a, b, c, d;
using P = pair<ll, ll>;
vector<P> vec = {
    {2,1},
    {1,2},
    {-1,2},
    {-2,1},
    {-2,-1},
    {-1,-2},
    {1,-2},
    {2,-1},
};

void _main() {
    cin >> a >> b >> c >> d;

    ll x, y;
    for (auto &p : vec) {
        x = a + p.first;
        y = b + p.second;
        for (auto &p : vec) {
            if (x == c + p.first && y == d + p.second) {
                Yes(1);
                return;
            }
        }
    }

    Yes(0);

}

int main() {
    _main();
    _main();
    _main();
    return 0;
}

// AC 21:29
