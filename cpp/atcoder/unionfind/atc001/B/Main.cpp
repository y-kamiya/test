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


int N, Q;

int root(int a, int par[]) {
    if (par[a] == a) return a;
    return par[a] = root(par[a], par);
}

bool same(int a, int b, int par[]) {
    return root(a, par) == root(b, par);
}

void unite(int a, int b, int par[]) {
    int x = root(a, par);
    int y = root(b, par);
    if (x != y) par[x] = y;
}

void _main() {
    cin >> N >> Q;

    int P[Q], A[Q], B[Q];
    REP(i, Q) cin >> P[i] >> A[i] >> B[i];

    int par[N];
    REP(i, N) par[i] = i;

    REP(i, Q) {
        // cout << i << P[i] << endl;
        if (P[i] == 1) {
            Yes(same(A[i], B[i], par));
            continue;
        }

        // if (!same(A[i], B[i], par)) par[A[i]] = B[i];
        unite(A[i], B[i], par);
    }
}

int main() {
    _main();
    return 0;
}

