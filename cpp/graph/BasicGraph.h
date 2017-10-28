#pragma once

class BasicGraph {
    public:
        BasicGraph();
        virtual ~BasicGraph();

    protected:
        std::vector<GraphVertex *> _verts;
};

