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
typedef pair<int, int> P;

int d[V];
vector<edge> G[V];

void dijkstra(int s) 
{
    priority_queue<P, vector<P>, greater<P> > que;
    fill(d, d + V, INF);
    d[s] = 0;
    que.push(P(0,s));

    while (!que.empty()) {
        P p = que.top();
        que.pop();
        int v = p.second;

        if (d[v] < p.first) continue;
        for (int i = 0; i < (int)G[v].size(); i++) {
            edge e = G[v][i];
            if (d[e.to] > d[v] + e.cost) {
                d[e.to] = d[v] + e.cost;
                que.push(P(d[e.to], e.to));
            }
        }
    }
}

int main() 
{
    int v, e;
    scanf("%d %d", &v, &e);
    for (int i = 0; i < e; i++) {
        edge ed,ed_r;
        scanf("%d %d %d", &(ed.from), &(ed.to), &(ed.cost));
        G[ed.from].push_back(ed);

        ed_r.from = ed.to;
        ed_r.to   = ed.from;
        ed_r.cost = ed.cost;
        G[ed_r.from].push_back(ed_r);
    }

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < (int)G[i].size(); j++) {
            printf("%d,%d,%d\n", G[i][j].from, G[i][j].to, G[i][j].cost);
        }
    }
    printf("\n");

    dijkstra(0);
    for (int i = 0; i < V; i++) {
        printf("%d: %d\n", i, d[i]);
    }
    return 0;
}

