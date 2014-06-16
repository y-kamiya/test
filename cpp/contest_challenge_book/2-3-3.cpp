/*
 * napsack problem (non 0,1)
 */
#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

typedef pair<int, int> P;

const int n = 3;
const int W = 7;
const int w[n] = {3,4,2};
const int v[n] = {4,5,3};

int dp[n+1][W+1];

void useDp() {
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= W; j++) {
            if (j < w[i]) {
                dp[i+1][j] = dp[i][j];
            } else {
                dp[i+1][j] = max(dp[i][j], dp[i+1][j-w[i]] + v[i]);
            }
        }
    }
}

int main() {
    memset(dp, 0, sizeof(dp));
    useDp();
    printf("%d\n", dp[n][W]);
    return 0;
}

