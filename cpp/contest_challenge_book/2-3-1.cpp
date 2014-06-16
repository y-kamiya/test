#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

typedef pair<int, int> P;

const int n = 4;
const int W = 5;
const int w[n] = {2,1,3,2};
const int v[n] = {3,2,4,2};

int dp[n+1][W+1];

int rec(int i, int j) {
    if (dp[i][j] >= 0) {
        return dp[i][j];
    }
    
    int res;
    if (i == n) {
        res = 0;
    } else if (j < w[i]) {
        res = rec(i + 1, j);
    } else {
        res = max(rec(i + 1, j), rec(i + 1, j - w[i]) + v[i]);
    }
    return dp[i][j] = res;
}

void useDp() {
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= W; j++) {
            if (j < w[i]) {
                dp[i+1][j] = dp[i][j];
            } else {
                dp[i+1][j] = max(dp[i][j], dp[i][j-w[i]] + v[i]);
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

