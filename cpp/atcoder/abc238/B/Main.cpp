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



int N;

void _main() {
    cin >> N;

    int A[N];
    REP(i, N) cin >> A[i];

    int B[N+2];
    B[0] = 0;
    B[N+1] = 360;
    FOR(i, 0, N) {
        B[i+1] = (B[i] + A[i]) % 360;
    }

    std::sort(B, B+N+2);
    int ans = 0;
    FORR(i, N+1, 1) {
        ans = std::max(ans, B[i] - B[i-1]);
    }

    cout << ans << endl;
}

int main() {
    _main();
    return 0;
}

// AC 21:20

