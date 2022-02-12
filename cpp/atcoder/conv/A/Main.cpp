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


int n;

void _main() {
    cin >> n;
    
    int a[n];
    REP(i, n) cin >> a[i];

    unordered_map<int, int> countMap;
    REP(i, n) {
        int l = a[i];

        int count = countMap.count(l) == 0 ? 0 : countMap[l];
        ++count;

        if (count >= 4) {
            YES(1);
            return;
        }

        countMap[l] = count;
    }

    YES(0);
}

int main() {
    _main();
    _main();
    return 0;
}

