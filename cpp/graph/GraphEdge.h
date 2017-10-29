#pragma once

class GraphEdge {
    public:
        GraphEdge();
        virtual ~GraphEdge();
        GrahpVertex *getTail() const {
            return _pTail;
        }
        GrahpVertex *getHead() const {
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

