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



int N, M;

using NodeMap = std::unordered_map<int, std::vector<int>>;

int f(int n, const NodeMap& nodeMap, int dp[]) {
    if (dp[n] != -1) return dp[n];

    int l = 0;
    if (nodeMap.count(n) != 0) {
        for (auto y : nodeMap.at(n)) {
            // cout << n << " - " << y << endl;
            l = max(l, f(y, nodeMap, dp)+1);
        }
        // cout << "=============" << endl;
    }

    // cout << n << ": " << l << endl;
    dp[n] = l;
    return l;
}

void _main() {
    int x[100005], y[100005];
    int dp[100005]; // iを始点とする場合の最長経路長

    cin >> N >> M;
    REP(i, M) cin >> x[i] >> y[i];
    memset(dp, -1, sizeof(dp));

    // 頂点iに対するエッジをmapとして構築しておく
    std::unordered_map<int, std::vector<int>> nodeMap;
    REP(i, M) {
        if (!nodeMap.count(x[i])) {
            nodeMap[x[i]] = vector<int>({y[i]});
        } else {
            nodeMap[x[i]].push_back(y[i]);
        }
    }

    // REP(i, N) {
    //     if (nodeMap.count(i)) {
    //         cout << i << ": ";
    //         for (const auto& x : nodeMap[i]) {
    //             cout << x << ", ";
    //         }
    //         cout << endl;
    //     }
    // }

    int l = 0;
    FOR(i, 1, N+1) {
        l = max(l, f(i, nodeMap, dp));
    }

    cout << l << endl;
}

int main() {
    _main();
    // cout << "==================" << endl;
    // _main();
    // cout << "==================" << endl;
    // _main();
    return 0;
}

// 解法見る
// iを始点とすると考えるのがポイント
// また、再帰じゃないと書きづらい
// ループさせる際にNとMを間違っていてデバッグに時間がかかった
// グローバルに変数を持っているので_mainを連続させて書くのは無駄にデバッグに時間がかかる
// なので各変数は_mainに書いて渡す形の方が結果的に楽かも
//
// nodeMapを作っておかないとTLE
//
