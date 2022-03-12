#include <bits/stdc++.h>
#include <iomanip>
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

static const int INF = 2147483647;
void _main() {
    int N;
    cin >> N;

    vector<int> X(N), Y(N);
    REP(i, N) cin >> X[i] >> Y[i];

    string S;
    cin >> S;

    // 位置yにおける<L向きの最大のx, R向き最小のx>
    map<int, pair<int, int>> rows;
    REP(i, N) {
        int y = Y[i];
        if (rows.count(y) == 0) {
            if (S[i] == 'L') rows[y] = {X[i], INF};
            if (S[i] == 'R') rows[y] = {-1, X[i]};
            continue;
        }

        if (S[i] == 'L') rows[y] = {max(rows[y].first, X[i]), rows[y].second};
        if (S[i] == 'R') rows[y] = {rows[y].first, min(rows[y].second, X[i])};
    }

    for (auto &p : rows) {
        int maxL = p.second.first;
        int minR = p.second.second;
        if (minR < maxL) {
            Yes(1);
            return;
        }
    }
    Yes(0);
}

int main() {
    _main();
    return 0;
}

// 2回WA
// 1度目はそもそもアルゴリズムの間違い
// 2度目はINFの値設定ミスでオーバーフローして負の値になっていたせい
// もったいない
