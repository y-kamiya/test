#include <bits/stdc++.h>
#include <string>
using namespace std;

using ll = long long;

#define REP(i,n) for(int i=0, i##_len=(n); i<i##_len; ++i)
#define REPR(i,n) for(int i=n;i>=0;i--)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define ALL(x) (x).begin(),(x).end()
#define UNIQUE(v) v.erase( unique(v.begin(), v.end()), v.end() );
#define YES(n) cout << ((n) ? "YES" : "NO"  ) << endl
#define Yes(n) cout << ((n) ? "Yes" : "No"  ) << endl

int N;
int H[100005];;

int main() {
    cin >> N;
    REP(i, N) cin >> H[i];

    int h = H[0];

    FOR(i, 1, N+1) {
        if (h < H[i]) {
            h = H[i];
        } else {
            break;
        }
    }

    cout << h << endl;
    return 0;
}

// 21:11
