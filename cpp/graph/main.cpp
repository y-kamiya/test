#include "Graph.h"
#include "GraphVertex.h"
#include "GraphEdge.h"

int main() {
    auto v1 = new GraphVertex();
    auto v2 = new GraphVertex();
    auto v3 = new GraphVertex();
    auto v4 = new GraphVertex();
    auto v5 = new GraphVertex();
    auto v6 = new GraphVertex();

    Graph<GraphVertex, GraphEdge> graph;
    graph.addVertex(v1);
    graph.addVertex(v2);
    graph.addVertex(v3);
    graph.addVertex(v4);
    graph.addVertex(v5);
    graph.addVertex(v6);

    graph.createEdge(v1, v2, 60, true);
    graph.createEdge(v1, v3, 65, true);
    graph.createEdge(v1, v4, 50, true);
    graph.createEdge(v1, v6, 40, true);
    graph.createEdge(v2, v3, 40, true);
    graph.createEdge(v4, v5, 45, true);
    graph.createEdge(v5, v6, 80, true);

    auto costFunc = [](GraphEdge *edge) {
        return edge->getCost();
    };
    std::vector<GraphVertex *> path;
    graph.computeBestPath(v2, v5, costFunc, path);

    for (auto v : path) {
        printf("%d\n", v->getIndex());
    }
}
