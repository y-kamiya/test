#pragma once

#include <vector>
#include <functional>

class GraphEdge;

class GraphVertex {
    public:
        GraphVertex() {
        }
        virtual ~GraphVertex() {
        }

        void addEdge(GraphEdge *pEdge) {
            _edges.push_back(pEdge);
        }
        std::vector<GraphEdge *> &getEdges() {
            return _edges;
        }

        int getIndex() const {
            return _index;
        }
        void setIndex(int index) {
            _index = index;
        }

        void setPathSearchCost(float cost) { 
            _pathSearchCost = cost;
        }
        float getPathSearchCost() const {
            return _pathSearchCost;
        }

        void setPredecessor(GraphVertex *pPred) {
            _pPredecessor = pPred;
        }
        GraphVertex *getPredecessor() const {
            return _pPredecessor;
        }

    protected:
        std::vector<GraphEdge *> _edges;
        int _index;

        float _pathSearchCost;
        GraphVertex *_pPredecessor;
};

class GraphVertexSearchCostComparer {
    public:
        bool operator()(const GraphVertex *v1, const GraphVertex *v2) const {
            return v1->getPathSearchCost() > v2->getPathSearchCost();
        }
};
