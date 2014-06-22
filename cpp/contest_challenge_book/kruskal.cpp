/*
 * 最小全域木(kruskal)
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

#include "union_find.cpp"

#define V 7
#define E 20
#define INF 10000000

using namespace std;

struct edge { int from, to, cost; };

edge es[E];


bool comp(const edge& e1, const edge& e2) {
    return e1.cost < e2.cost;
}

int kruskal() {
    sort(es, es + E, comp);

    UnionFind *unionfind = new UnionFind();
    unionfind->init(V);
    int res = 0;

    for (int i = 0; i < E; i++) {
        edge e = es[i];
        if (!unionfind->same(e.from, e.to)) {
            unionfind->unite(e.from, e.to);
            res += e.cost;
        }
    }
    return res;
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

    int res = kruskal();
    printf("%d\n", res);

    return 0;
}

