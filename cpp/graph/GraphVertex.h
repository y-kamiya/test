#pragma once

class GraphVertex {
    public:
        GraphVertex();
        virtual ~GraphVertex();

        void AddEdge(GraphEdge *pEdge);
        std::vector<GraphEdge *> &getEdges();
        int getIndex() const;
        void setIndex(int index);

        void setPathSearchCost(float cost);
        flaot getPathSearchCost() const;

        void setPredecessor(GraphVertex *pPred);
        GraphVertex *getPredecessor() const;

    protected:
        std::vector<GraphEdge *> _edges;
        int index;

        float pathSearchCost;
        GraphVertex *pPredecessor;
};

