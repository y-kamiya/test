/*
 * napsack problem (0,1 reverse)
 */
#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

const int INF = 10000000;
const int n = 3;
const int m = 5;
const int W = 10;
const int w[n] = {3,4,2};
const int v[n] = {4,5,3};

int dp[n+1][n*m+1];

void useDp() {
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= n * m; j++) {
            if (j < v[i]) {
                dp[i+1][j] = dp[i][j];
            } else {
                dp[i+1][j] = min(dp[i][j], dp[i+1][j-v[i]] + w[i]);
            }
        }
    }
}

int main() {
    for (int j = 0; j <= n * m; j++) {
        dp[0][j] = INF;
    }
    useDp();
    int res = 0;
    for (int j = 0; j < n * m; j++) {
        if (dp[n][j] <= W) res = max(j, res);
    }
    printf("%d\n", res);
    return 0;
}

