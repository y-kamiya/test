#include <iostream>
using namespace std;

struct Point {
    int t;
    int x;
    int y;

    bool operator==(const Point& rhs) const {
        return t == rhs.t && x == rhs.x && y == rhs.y;
    }
};

Point operator+(const Point& lhs, const Point& rhs) {
    Point p;
    p.t = lhs.t + rhs.t;
    p.x = lhs.x + rhs.x;
    p.y = lhs.y + rhs.y;
    return p;
}

Point moves[4] = {
    {1, 1, 0},
    {1, -1, 0},
    {1, 0, 1},
    {1, 0, -1},
};

bool dfs(const Point& s, const Point& g) {
    if (s == g) return true;
    if (s.t == g.t) return false;

    for (Point p : moves) {
        if (s.x + p.x < 0) continue;
        if (s.y + p.y < 0) continue;
        if (dfs(s + p, g)) return true;
    }

    return false;
}


int main() {
    int N;
    cin >> N;

    Point ps[N+1];
    ps[0].t = ps[0].x = ps[0].y = 0;
    for (int i = 1; i <= N; ++i) {
        cin >> ps[i].t >> ps[i].x >> ps[i].y;
    }
    
    for (int i = 0; i < N; ++i) {
        bool canReach = dfs(ps[i], ps[i+1]);
        if (!canReach) {
            cout << "NO" << endl;
            return 0;
        }
    }

    cout << "YES" << endl;

    return 0;
}

