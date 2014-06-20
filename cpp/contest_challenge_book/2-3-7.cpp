/*
 * 分割数
 */
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int n = 4;
const int m = 3;
const int M = 10000;

int dp[m+1][n+1];

void useDp() {
    for (int i = 1; i <= m; i++) {
        dp[0][0] = 1;
        for (int j = 0; j <= n; j++) {
            if (j - i >= 0) {
                dp[i][j] = (dp[i][j-i] + dp[i-1][j]) % M;
            } else {
                dp[i][j] = dp[i-1][j];
            }
        }
    }
}

int main() {
    memset(dp, 0, sizeof(dp));
    useDp();
    printf("%d\n", dp[m][n]);
    return 0;
}

