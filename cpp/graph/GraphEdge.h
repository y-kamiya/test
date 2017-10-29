#pragma once

class GraphVertex;

class GraphEdge {
    public:
        GraphEdge(float cost) {
            _baseCost = cost;
        }
        virtual ~GraphEdge() {
        }

        GraphVertex *getTail() const {
            return _pTail;
        }
        GraphVertex *getHead() const {
            return _pHead;
        }
        void setTail(GraphVertex *pVert) {
            _pTail = pVert;
        }
        void setHead(GraphVertex *pVert) {
            _pHead = pVert;
        }
        virtual float getCost() const {
            return _baseCost;
        }
        
    protected:
        GraphVertex *_pTail;
        GraphVertex *_pHead;
        float _baseCost;
};

