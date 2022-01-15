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

int N, a[2][105];

int sum(int j) {
    int total = 0;
    FOR(jj, 0, j+1) total += a[0][jj];
    FOR(jj, j, N) total += a[1][jj];
    return total;
}

int main() {
    cin >> N;
    REP(i, N) cin >> a[0][i];
    REP(i, N) cin >> a[1][i];

    int maxCnt = 0;
    REP(j, N) {
        maxCnt = max(maxCnt, sum(j));
    }

    cout << maxCnt << endl;

    return 0;
}


