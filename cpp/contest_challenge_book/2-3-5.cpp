/*
 * 個数制限付き部分和
 */
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

const int n = 3;
const int a[n] = {3,5,8};
const int m[n] = {3,2,2};
const int K = 17;

int dp[n+1][K+1];

void useDp() {
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= K; j++) {
            if (dp[i][j] >= 0) {
                dp[i+1][j] = m[i];
            } else if (j < a[i] || dp[i+1][j-a[i]] <= 0) {
                dp[i+1][j] = -1;
            } else {
                dp[i+1][j] = dp[i+1][j-a[i]] - 1;
            }
        }
    }
}

int main() {
    memset(dp, -1, sizeof(dp));
    useDp();
    bool isYes = false;
    for (int i = 0; i <= n; i++) {
        if (dp[i][K] >= 0) {
            isYes = true;
            break;
        }
    }
    if (isYes) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    return 0;
}

