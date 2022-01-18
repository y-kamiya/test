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

const int INF = 1<<29;

// 典型的な DP (動的計画法) のパターンを整理 Part 1 ～ ナップサック DP 編 ～
// https://qiita.com/drken/items/a5e6fe22863b7992efdb

// aの要素の和の最大値を出力
void dp_simple(vector<int> a) {
    int n = a.size();

    int dp[n+1];
    dp[0] = 0;

    FOR(i, 0, n) {
        dp[i+1] = max(dp[i], dp[i] + a[i]);
    }

    cout << dp[n] << endl;
}

// Wを超えない重さで最大の価値となる場合
void dp_napsack(int W, vector<int> weight, vector<int> value) {
    int n = weight.size();
    int dp[n+1][W+1];
    REP(i, n+1) REP(j, W+1) dp[i][j] = 0;

    FOR(i, 0, n) {
        int w = weight[i];
        int v = value[i];
        FOR(j, 0, W+1) {
            if (0 <= j - w) {
                dp[i+1][j] = max(dp[i][j], dp[i][j - w] + v);
            } else {
                dp[i+1][j] = dp[i][j];
            }
        }
    }
    cout << dp[n][W] << endl;
}

// a[]の中の数字のいくつかの和でAとなるものはあるか
void dp_sum_check(int A, vector<int> a) {
    int n = a.size();
    bool dp[n+1][A+1];

    memset(dp, 0, sizeof(dp));
    dp[0][0] = true;

    FOR(i, 0, n) {
        FOR(j, 0, A+1) {
            dp[i+1][j] |= dp[i][j];
            if (a[i] <= j) {
                dp[i+1][j] |= dp[i][j - a[i]];
            }
        }
    }
    cout << dp[n][A] << endl;
}

// a[]の中の数字のいくつかの和でAとなる選び方は何通りか
void dp_sum_count(int A, vector<int> a) {
    int n = a.size();
    int dp[n+1][A+1];

    memset(dp, 0, sizeof(dp));;
    dp[0][0] = 1;

    FOR(i, 0, n) {
        FOR(j, 0, A+1) {
            dp[i+1][j] += dp[i][j];
            if (a[i] <= j) dp[i+1][j] += dp[i][j - a[i]];
        }
    }
    cout << dp[n][A] << endl;
}

// a[]の中の数字のいくつかの和でAとなる選び方で、最小個数のものは何個か
void dp_sum_min_select(int A, vector<int> a) {
    int n = a.size();
    int dp[n+1][A+1];

    REP(i, n+1) REP(j, A+1) dp[i][j] = INF;
    dp[0][0] = 0;

    FOR(i, 0, n) {
        FOR(j, 0, A+1) {
            if (a[i] <= j) dp[i+1][j] = min(dp[i][j], dp[i][j - a[i]] + 1);
            else dp[i+1][j] = dp[i][j];
        }
    }

    if (dp[n][A] == INF) cout << -1 << endl;
    else cout << dp[n][A] << endl;
}

// SとTの最長共通部分列
void dp_lcs(string S, string T) {
    int ns = S.size();
    int nt = T.size();
    int dp[ns+1][nt+1]; // Sのns文字目までとntのj文字目までのLCS

    memset(dp, 0, sizeof(dp));

    FOR(i, 0, ns) {
        FOR(j ,0, nt) {
            if (S[i] == T[j]) dp[i+1][j+1] = dp[i][j] + 1;
            else dp[i+1][j+1] = max(dp[i+1][j], dp[i][j+1]);
        }
    }
    cout << dp[ns][nt] << endl;
}

// a[]とb[]の最小コスト弾性マッチング
void dp_least_cost_matching(vector<vector<int>> c) {
    int n = c.size();
    int m = c[0].size();
    int dp[n+1][m+1]; //a(i)までとb(j)まででの弾性マッチングの最小コスト
    
    REP(i, n+1) REP(j, m+1) dp[i][j] = INF;
    dp[0][0] = 0;

    FOR(i, 0, n) {
        FOR(j, 0, m) {
            dp[i+1][j+1] = min(dp[i+1][j], dp[i][j+1]) + c[i][j];
            dp[i+1][j+1] = min(dp[i+1][j+1], dp[i][j] + c[i][j]);
        }
    }
    cout << dp[n][m] << endl;
}

// レーベンシュタイン距離
// cf. https://o-treetree.hatenablog.com/entry/DPL1E
void dp_diff(string S, string T) {
    int ns = S.size();
    int nt = T.size();
    int dp[ns+1][nt+1];

    REP(i, ns) REP(j, nt) dp[i][j] = INF;
    dp[0][0] = 0;

    FOR(i, 0, ns) {
        FOR(j, 0, nt) {
            dp[i+1][j+1] = min(dp[i+1][j], dp[i][j+1]) + 1;
            if (S[i] == T[j]) dp[i+1][j+1] = min(dp[i+1][j+1], dp[i][j]);
            else dp[i+1][j+1] = min(dp[i+1][j+1], dp[i][j] + 1);
        }
    }
    cout << dp[ns][nt] << endl;
}

// 区間DP
// cf. https://kutimoti.hatenablog.com/entry/2018/03/10/220819
void dp_zone(vector<int> a) {
    int n = a.size();
    int dp[n+1][n+1]; // 区間[l, r)で取り除けるブロックの数の最大値

    memset(dp, 0, sizeof(dp));

    FOR(j, 2, n+1) {
        FOR(i, 0, n) {
            int r = i + j;
            if (n < r) break;

            if (dp[i+1][r-1] == j-2 && abs(a[r-1] - a[i]) <= 1) {
                dp[i][r] = j;
            } else {
                FOR(mid, i+1, r-1) {
                    dp[i][r] = max(dp[i][r], dp[i][mid] + dp[mid][r]);
                    // cout << i << "," << mid << "," << j << endl;
                }
            }
        }
    }

    cout << dp[0][n] << endl;
}

int main() {
    // dp_simple({7, -6, 9});
    // dp_napsack(9, {2,1,3,2,1,5}, {3,2,6,1,3,85});
    // dp_sum_check(10, {7,5,3});
    // dp_sum_count(12, {7,5,3,1,8});
    // dp_sum_min_select(12, {7,5,3,1,8});
    // dp_lcs("abcde", "acbef");
    // dp_least_cost_matching({{1,2,3},{4,3,2}});
    dp_zone({5, 1, 2, 3, 6});
    dp_zone({8,7,1,4,3,5,4,1,6,8,10,4,6,5});
}

