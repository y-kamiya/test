/*
 * 最小全域木(prim)
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

#define V 7
#define E 20
#define INF 10000000

using namespace std;

bool used[V];
int cost[V][V];
int mincost[V];


int prim() {
    fill(mincost, mincost + V, INF);
    fill(used, used + V, false);

    mincost[0] = 0;
    int res = 0;

    while (true) {
        int v = -1;
        for (int u = 0; u < V; u++) {
            if (!used[u] && (v == -1 || mincost[u] < mincost[v])) v = u;
        }
        if (v == -1) break;

        used[v] = true;
        res += mincost[v];

        for (int u = 0; u < V; u++) {
            mincost[u] = min(mincost[u], cost[v][u]);
        }
    }
    return res;
}

int main() {
    int v, e;
    scanf("%d %d", &v, &e);

    for (int i = 0; i < V; i++) {
        fill(cost[i], cost[i] + V, INF);
    }
    for (int i = 0; i < e; i++) {
        int from, to, c;
        scanf("%d %d %d", &(from), &(to), &(c));
        cost[from][to] = c;
        cost[to][from] = c;
    }

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%d ", cost[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    int res = prim();
    printf("res: %d\n", res);
    for (int i = 0; i < V; i++) {
        printf("%d: %d\n", i, mincost[i]);
    }
    return 0;
}

