/*
 * Conscription (POJ no.3723)
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

#define N 5
#define M 5
#define R 8
#define V N+M
#define INF 10000000

using namespace std;

int cost[V][V];
int mincost[V];
bool used[V];

int prim() 
{
    int res = 0;
    while (true) {
        int v = -1;
        for (int u = 0; u < V; u++) {
            if (!used[u] && (v == -1 || mincost[u] < mincost[v])) v = u;
        }
        if (v == -1) break;

        res += mincost[v];
        cout << mincost[v] << endl;
        used[v] = true;
        for (int u = 0; u < V; u++) {
            mincost[u] = min(mincost[u], cost[u][v]);
        }
    }
    return res;
}

int main() 
{
    for (int i = 0; i < V; i++) {
        fill(cost[i], cost[i] + V, 10000);
    }
    fill(mincost, mincost + V, 10000);
    fill(used, used + V, false);

    int n, m, r;
    scanf("%d %d %d", &n, &m, &r);
    for (int i = 0; i < r; i++) {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        cost[u][n+v] = 10000 - c;
        cost[n+v][u] = 10000 - c;
    }

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cout << cost[i][j] << " ";
        }
        cout << endl;
    }
    int res = prim();
    printf("%d\n", res);

    return 0;
}

