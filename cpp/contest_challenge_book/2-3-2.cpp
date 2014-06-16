/*
 * LDS
 */
#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

const int n = 4;
const int m = 4;
const char s[n+1] = "abcd";
const char t[m+1] = "aecd";

int dp[n+1][m+1];

void useDp() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i] == t[j]) {
                dp[i+1][j+1] = dp[i][j] + 1;
            } else {
                dp[i+1][j+1] = max(dp[i+1][j], dp[i][j+1]);
            }
        }
    }
}

int main() {
    memset(dp, 0, sizeof(dp));
    useDp();
    printf("%d\n", dp[n][m]);
    return 0;
}

