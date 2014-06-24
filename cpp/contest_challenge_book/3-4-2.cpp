/*
 * traveling by stagecoach
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>
#include <set>

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

#define INF 1000000

using namespace std;

typedef long long ll;
typedef vector<int> V;

const int n = 2, m = 4, a = 2, b = 1;
const int t[n] = {3, 1};
int cost[m][m];
double dp[1 << n][m];

void solve()
{
    for (int i = 0; i < 1 << n; i++) {
        fill(dp[i], dp[i] + m, INF);
    }
    dp[(1 << n) - 1][a - 1] = 0;
    double res = INF;
    for ( int S = (1 << n) - 1; S >= 0; S--) {
        res = min(res, dp[S][b - 1]);
        for (int v = 0; v < m; v++) {
            for (int i = 0; i < n; i++) {
                if (S >> i & 1) {
                    for (int u = 0; u < m; u++) {
                        if (cost[v][u] >= 0) {
                            int Si = S & ~(1 << i);
                            dp[Si][u] = min(dp[Si][u], dp[S][v] + (double)cost[v][u] / t[i]);
                        }
                    }
                }
            }
        }
    }
    if (res == INF) {
        printf("Impossible\n");
    } else {
        printf("%.3f\n", res);
    }
}

int main() 
{
    int v, e;
    scanf("%d %d", &v, &e);

    for (int i = 0; i < v; i++) {
        fill(cost[i], cost[i] + v, INF);
    }
    for (int i = 0; i < e; i++) {
        int from, to, c;
        scanf("%d %d %d", &(from), &(to), &(c));
        cost[from][to] = c;
    }

    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            printf("%d ", cost[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    solve();
    return 0;
}
