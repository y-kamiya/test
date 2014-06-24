/*
 * traveling salesman problem
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

const int n = 5;
int cost[n][n];
int dp[1 << n][n];

int solve(int S, int v)
{
    if (dp[S][v] >= 0) {
        return dp[S][v];
    }

    if (S == (1 << n) - 1 && v == 0) {
        return dp[S][v] = 0;
    }

    int res = INF;
    for (int u = 0; u < n; u++) {
        if (!(S >> u & 1)) {
            res = min(res, solve(S | 1 << u, u) + cost[v][u]);
        }
    }
    return dp[S][v] = res;
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

    memset(dp, -1, sizeof(dp));
    printf("%d\n", solve(0, 0));
    return 0;
}
