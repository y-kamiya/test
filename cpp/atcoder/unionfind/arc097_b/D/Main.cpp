#include <algorithm>
#include <bits/stdc++.h>
#include <unordered_map>
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

static const int N_MAX = 200005;

int N, M;
int par[N_MAX];


int root(int a) {
    if (par[a] == a) return a;
    return par[a] = root(par[a]);
}

bool same(int a, int b) {
    return root(a) == root(b);
}

void unite(int a, int b) {
    int x = root(a);
    int y = root(b);
    if (x != y) par[x] = y;
}

void _main() {
    cin >> N >> M;

    int p[N+1];
    FOR(i, 1, N+1) cin >> p[i];

    int x[M], y[M];
    REP(i, M) cin >> x[i] >> y[i];

    REP(i, N_MAX) par[i] = i;

    REP(i, M) {
        unite(x[i], y[i]);
    }

    vector<int> correct = {};
    FOR(i, 1, N+1) {
        if (i == p[i]) correct.push_back(p[i]);
    }
    sort(ALL(correct));

    std::unordered_map<int, vector<int>> group;
    FOR(i, 1, N+1) {
        int r = root(i);
        if (group.count(r) == 0) group[r] = {};
        group[r].push_back(i);
    }

    int maxCount = 0;
    for (auto pair : group) {
        vector<int> values = {};
        for (auto v : pair.second) values.push_back(p[v]);

        sort(ALL(pair.second));
        sort(ALL(values));

        vector<int> intersection;
        set_intersection(ALL(pair.second), ALL(values), back_inserter(intersection));

        // cout << "index: ";
        // for (auto v: pair.second) {
        //     cout << v << " ";
        // }
        // cout << endl;
        // cout << "value: ";
        // for (auto v: values) {
        //     cout << v << " ";
        // }
        // cout << endl;

        vector<int> uni;
        set_union(ALL(intersection), ALL(correct), back_inserter(uni));
        maxCount = std::max(maxCount, (int)uni.size());
    }

    cout << maxCount << endl;
}

int main() {
    _main();
    _main();
    _main();
    _main();
    return 0;
}

// union, intersectionなど取る必要なく、indexとp[index]が同じ木かどうかをsameで判定するだけでよかった
// https://qiita.com/ofutonton/items/550c984f08e39a189ca6

