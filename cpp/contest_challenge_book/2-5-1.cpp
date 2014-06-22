/*
 * Roadblocks (POJ no.3255)
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

int dist[V];
int dist2[V];
vector<edge> G[V];

void dijkstra(int s) 
{
    priority_queue<P, vector<P>, greater<P> > que;
    fill(dist, dist + V, INF);
    fill(dist2, dist2 + V, INF);

    dist[0] = 0;
    dist2[0] = 0;
    que.push(P(0, 0));

    while (!que.empty()) {
        P p = que.top();
        que.pop();
        int d = p.first;
        int v = p.second;

        if (dist2[v] < d) continue;

        for (int i = 0; i < (int)G[v].size(); i++) {
            edge &e = G[v][i];
            int dd = dist[v] + e.cost;
            if (dist[e.to] > dd) {
                swap(dist[e.to], dd);
                que.push(P(dist[e.to], e.to));
            } 
            if (dist2[e.to] > dd && dist[e.to] < dd) {
                swap(dist2[e.to], dd);
                que.push(P(dist2[e.to], e.to));
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
    printf("dist\n");
    for (int i = 0; i < V; i++) {
        printf("%d: %d\n", i, dist[i]);
    }
    printf("\n\n");
    printf("dist2\n");
    for (int i = 0; i < V; i++) {
        printf("%d: %d\n", i, dist2[i]);
    }
    return 0;
}

