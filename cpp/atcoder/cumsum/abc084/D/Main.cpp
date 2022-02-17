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


int Q;

bool isPrime(int n) {
    auto sqrtN = (int)sqrt(n);
    FOR(i, 2, sqrtN+1) {
        if (n % i == 0) return false;
    }
    return true;
}

bitset<1000000> prime(0);
bool eratos(int n) {
    FOR(i, 2, n+1) prime.set(i);
    FOR(i, 2, n+1) {
        if (prime[i]) {
            for (int j = i*2; j <= n; j += i) {
                prime.reset(j);
            }
        }
    }
}

void _main() {
    cin >> Q;

    int a[100001];
    a[0] = a[1] = 0;
    FOR(i, 3, 100001) {
        if (i % 2 == 0) continue;

        a[i] = a[i-2];
        int n = (i+1) / 2;
        if (isPrime(i) && isPrime(n)) ++a[i];
    }

    // REP(i, 20) {
    //     if (i%2 == 0) continue;
    //     cout << i << ": " << a[i] << endl;
    // }

    int l, r;
    REP(i, Q) {
        cin >> l >> r;
        int ans;
        if (l == 1) ans = a[r];
        else ans = a[r] - a[l-2];
        cout << ans << endl;
    }
}

int main() {
    _main();
    // cout <<  endl;
    // _main();
    // cout <<  endl;
    // _main();
    return 0;
}

