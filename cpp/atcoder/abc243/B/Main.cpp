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

    vector<int> A(N), B(N);
    REP(i, N) cin >> A[i];
    REP(i, N) cin >> B[i];

    int a = 0;
    int b = 0;
    REP(i, N) {
        if (A[i] == B[i]) {
            ++a;
            continue;
        }
        REP(j, N) {
            if (A[i] == B[j]) {
                ++b;
                break;
            }
        }
    }

    cout << a << endl;
    cout << b << endl;
}

int main() {
    _main();
    return 0;
}

