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

void _main() {
    int N;
    cin >> N;

    int MAX = 2 * N + 1;

    vector<int> done(MAX, 0);
    int a;

    while (true) {
        // REP(i, MAX) cout << done[i] << ", ";
        // cout << endl;

        REP(i, MAX) {
            if (done[i] == 0) {
                cout << i+1 << endl;
                done[i] = 1;
                break;
            }
        }

        cin >> a;
        if (a == 0) return;

        --a;
        done[a] = 1;
    }
}

int main() {
    _main();
    return 0;
}

