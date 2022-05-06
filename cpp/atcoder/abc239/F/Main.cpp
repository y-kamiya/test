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

int N, M;

int root(int a, vector<int>& par) {
    return par[a] = root(par[a], par);
}

bool same(int a, int b, vector<int>& par) {
    return root(a, par) == root(b, par);
}

void unite(int a, int b, vector<int>& par) {
    int x = root(a, par);
    int y = root(b, par);
    if (x != y) par[x] = y;
}

void _main() {
    cin >> N >> M;
    
    vector<int> D(N+1);
    FOR(i, 1, N+1) cin >> D[i];

    vector<int> par(N+1);
    FOR(i, 1, N+1) par[i] = i;

    int A, B;
    REP(i, M) {
        cin >> A >> B;
        unite(A, B, par);
    }

}

int main() {
    _main();
    return 0;
}

