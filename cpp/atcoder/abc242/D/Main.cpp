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


ll modpow(ll a, ll n) {
    ll res = 1;
    while (n > 0) {
        if (n & 1) res *= a;
        a *= a;
        n >>= 1;
    }
    return res;
}

map<char, ll> c2i = {{'A', 0}, {'B', 1}, {'C', 2}};
map<ll, char> i2c = {{0, 'A'}, {1, 'B'}, {2, 'C'}};

int func(ll t, ll k, const string &S) {
    if (t == 0) {
        return c2i[S[k]];
    }

    if (k == 0) {
        ll n = c2i[S[0]];
        return (n + t) % 3;
    }

    if (k % 2 == 1) return (func(t-1, k/2, S) + 2) % 3;
    else return (func(t-1, k/2, S) + 1) % 3;
}

void _main() {
    string S;
    cin >> S;
    int Q;
    cin >> Q;

    ll t, k;
    REP(i, Q) {
        cin >> t >> k;
        cout << i2c[func(t, k-1, S)] << endl;
    }
}

int main() {
    _main();
    return 0;
}


// 考え方自体は合っていたが、f(t,k)として答えを返す関数を定義するというは浮かばず
// 関数を定義して再帰でというところまで解法を見て後は普通に実装できた(が、30分くらいかかった)
