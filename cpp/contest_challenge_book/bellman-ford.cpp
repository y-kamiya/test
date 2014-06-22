/*
 * bellman ford
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

edge es[E];
int d[V];


void shortest_path(int s) {
    for (int i = 0; i < V; i++) {
        d[i] = INF;
    }
    d[s] = 0;
    while (true) {
        bool update = false;
        for (int j = 0; j < E; j++) {
            edge e = es[j];
            if (e.from == INF) continue;
            if (d[e.from] + e.cost < d[e.to]) {
                d[e.to] = d[e.from] + e.cost;
                update = true;
            } 
        }
        if (!update) break;
    }

}

int main() {
    int v, e;
    scanf("%d %d", &v, &e);
    for (int i = 0; i < e; i++) {
        edge ed,ed_r;
        scanf("%d %d %d", &(ed.from), &(ed.to), &(ed.cost));
        es[2*i] = ed;

        ed_r.from = ed.to;
        ed_r.to   = ed.from;
        ed_r.cost = ed.cost;
        es[2*i+1] = ed_r;
    }

    for (int i = 0; i < e; i++) {
        printf("%d,%d,%d\n", es[i].from, es[i].to, es[i].cost);
    }
    printf("\n");

    shortest_path(0);
    for (int i = 0; i < V; i++) {
        printf("%d: %d\n", i, d[i]);
    }
    return 0;
}

