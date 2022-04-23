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

void print() { cout << endl; }

template<typename Head, typename... Tail>
void print(Head h, Tail... t) {
    cout << h << " "; print(t...);
}
#ifdef _DEBUG
#define DEBUG(...) print(__VA_ARGS__)
#else
#define DEBUG(...)
#endif


void _main() {
    int A, B, C, D, E, F, X;
    cin >> A >> B >> C >> D >> E >> F >> X;

    int at = X / (A + C) * A;
    int bt = min(X % (A + C), A);
    int takahashi = (at + bt) * B;

    int ct = X / (D + F) * D;
    int dt = min(X % (D + F), D);
    int aoki = (ct + dt) * E;

    if (takahashi < aoki) cout << "Aoki" << endl;
    else if (takahashi > aoki) cout << "Takahashi" << endl;
    else cout << "Draw" << endl;
}

int main() {
    _main();
    return 0;
}

