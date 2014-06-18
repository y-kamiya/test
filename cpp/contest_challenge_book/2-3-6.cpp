/*
 * LIS
 */
#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

const int n = 5;
const int a[n] = {4,2,3,1,5};

int dp[n+1];

int useDp() {
    int res = 0;
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        res = max(res, dp[i]);
    }
    return res;
}

int main() {
    memset(dp, 0, sizeof(dp));
    int res = useDp();
    printf("%d\n", res);
    return 0;
}

