#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define rep(i,n) for(int i=0, i##_len=(n); i<i##_len; ++i)
#define all(x) (x).begin(),(x).end()
#define UNIQUE(v) v.erase( unique(v.begin(), v.end()), v.end() );
#define YES(n) cout << ((n) ? "YES" : "NO"  ) << endl
#define Yes(n) cout << ((n) ? "Yes" : "No"  ) << endl

int main() {
    int A, B, C, D;
    cin >> A >> B >> C >> D;

    int cnt = 0;
    rep(i, 101) {
        if (A <= i && i < B && C <= i && i < D) ++cnt;
    }

    cout << cnt << endl;

    return 0;
}


