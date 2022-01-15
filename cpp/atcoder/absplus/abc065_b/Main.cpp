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

int main() {
    int N, a[100005];
    cin >> N;
    REP(i, N) cin >> a[i];

    int done[N];
    REP(i, N) done[i] = 0;
    done[1] = 1;

    int cnt = 0;
    int current = 0;
    REP(i, N) {
        if (current == 1) {
            break;
        }
        if (done[current] == 1) {
            cnt = -1;
            break;
        }
        ++cnt;
        done[current] = 1;
        current = a[current] - 1;
    }

    cout << cnt << endl;

    return 0;
}

