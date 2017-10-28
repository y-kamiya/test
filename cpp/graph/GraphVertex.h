#pragma once

class GraphVertex {
    public:
        GraphVertex();
        virtual ~GraphVertex();

        void AddEdge(GraphVertex *pNeighbor);

    protected:
        std::vector<GraphVertex *> _neighbors;
};

