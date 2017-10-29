#pragma once

template<class VERTEX, class EDGE>
class Graph {
    public:
        Graph() {
            _verts.reserve(100);
            _edges.reserve(100);
        }
        virtual ~Graph();

        VERTEX *getVertex(int index) {
            return _verts[index];
        }
        EDGE *getEdge(int index) {
            return _edges[index];
        }

        void addVertex(VERTEX *vert);
        bool createEdge(VERTEX *pTail, VERTEX *pHead, bool isTwoWay = true);
        float computeBestPath(VERTEX *pStart, VERTEX pGoal,
                std::function<float(EDGE *)>, std::vector<VERTEX *> &path);

    protected:
        std::vector<VERTEX *> _verts;
        std::vector<EDGE *> _edges;

        void InitializePathSearch();
};

template<class VERTEX, class EDGE>
Graph<VERTEX, EDGE>::~Graph() {
    for (auto vert : _verts) {
        delete(vert);
    }
    for (auto pEdge : _edges) {
        delete(pEdge);
    }
    _verts.clear();
    _edges.clear();
}

template<class VERTEX, class EDGE>
void Graph<VERTEX, EDGE>::addVertex(VERTEX *vert) {
    vert->setIndex(static_cast<int>(_verts.size()));
    _verts.push_back(vert);
}

template<class VERTEX, class EDGE>
void Graph<VERTEX, EDGE>::createEdge(VERTEX *pTail, VERTEX *pHead, bool isTwoWay) {
    EDGE *pEdge = new EDGE;
    pEdge->setTail(pTail);
    pEdge->setHead(pHead);
    pTail->addEdge(pEdge);

    if (isTwoWay) {
        EDGE *pEdge2 = new EDGE;
        pEdge2->setTail(pHead);
        pEdge2->setHead(pTail);
        pHead->addEdge(pEdge2);
    }
}

template<class VERTEX, class EDGE>
void Graph<VERTEX, EDGE>::InitializePathSearch() {
    for (auto vert : _verts) {
        setPathSearchCost(FLT_MAX);
        setPredecessor(nullptr);
    }
}

template<class VERTEX, class EDGE>
float computeBestPath(VERTEX *pStart, VERTEX pGoal,
        std::function<float(EDGE *)> costFunc, std::vector<VERTEX *> &path) {

    InitializePathSearch();
    priority_queue<VERTEX *, std::vector<VERTEX *>, GraphVertexSearchCostComparer> fringe;

    pStart->setPathSearchCost(0.0f);
    VERTEX *pCurrentVertex = pStart;
    fringe.push(pStart);
    auto totalCostToGoal = FLT_MAX;

    while (!fringe.empty()) {
        std::vector<EDGE *> &edges = pCurrentVertex->getEdges();
        for (auto pEdge : edges) {
            auto pNeighbor = static_cast<VERTEX *>(pEdge->getHead());
            if (pNeighbor == pCurrentVertex->getPredecessor()) {
                continue;
            }

            float edgeCost = costFunc(pEdge);
            float newCostToThisVertex = pCurrentVertex->getPathSearchCost() + edgeCost;
            float currentCostToThisVertex = pNeighbor->getPathSearchCost();

            if (newCostToThisVertex < currentCostToThisVertex &&
                    newCostToThisVertex < totalCostToGoal) {
                pNeighbor->setPathSearchCost(newCostToThisVertex);
                pNeighbor->setPredecessor(pCurrentVertex);
                if (pNeighbor == pGoal) {
                    totalCostToGoal = newCostToThisVertex;
                }
                fringe.push_back(pNeighbor);
            }
        }

        fringe.pop();
        if (!fringe.empty()) {
            pCurrentVertex = fringe.top();
        }
    }

    if (totalCostToGoal < FLT_MAX) {
        VERTEX *pPathVertex = pGoal;
        do {
            path.push_back(pPathVertex);
            pPathVertex = static_cast<VERTEX *>(pPathVertex->getPredecessor());
        } while (pPathVertex != pStart);
        path.push_back(pStart);
    }
    return totalCostToGoal;
}
