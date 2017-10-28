#pragma once

class NavigationNode : public GraphVertex {
    public:
        NavigationNode();
        NavigationNode(const Vector2d &pos);
        virtual ~NavigationNode();

        const Vector2d &getPos() const {
            return _pos;
        }
        void setPos(const Vector2d &pos) {
            _pos = pos;
        }

    protected:
        Vector2d _pos;
};

