/*
 * dijkstra (隣接行列)
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

struct edge { int from, to, cost; };

int d[V];
bool used[V];
int cost[V][V];


void dijkstra(int s) {
    fill(d, d + V, INF);
    fill(used, used + V, false);
    d[s] = 0;

    while (true) {
        int v = -1;
        for (int u = 0; u < V; u++) {
            if (!used[u] && (v == -1 || d[u] < d[v])) v = u;
        }
        if (v == -1) break;

        used[v] = true;

        for (int u = 0; u < V; u++) {
            d[u] = min(d[u], d[v] + cost[v][u]);
        }
    }
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

    dijkstra(0);
    for (int i = 0; i < V; i++) {
        printf("%d: %d\n", i, d[i]);
    }
    return 0;
}

