/*
 * warshall floyd
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


int d[V][V];

void warshall_floyd() {
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
}

int main() {
    int v, e;
    scanf("%d %d", &v, &e);

    for (int i = 0; i < V; i++) {
        fill(d[i], d[i] + V, INF);
        d[i][i] = 0;
    }
    for (int i = 0; i < e; i++) {
        int from, to, c;
        scanf("%d %d %d", &(from), &(to), &(c));
        d[from][to] = c;
        d[to][from] = c;
    }

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%d ", d[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    warshall_floyd();
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%d-%d: %d\n", i, j, d[i][j]);
        }
    }
    return 0;
}

