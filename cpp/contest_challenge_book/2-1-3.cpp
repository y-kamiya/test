#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

typedef pair<int, int> P;

const int n = 5;
const int m = 6;
const int INF = 100000000;
char maze[n][m+1] = {
    "##S###",
    ".....#",
    ".##.##",
    "#....#",
    "#G####",
};

int d[n][m+1];
int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};

P getStartOrGoal(char c) {
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++) { 
            if (maze[i][j] == c) return P(i, j);
        }
    }
    return make_pair(0,0);
}

bool inMaze(P p) {
    int x = p.first, y = p.second;
    
    if (0 <= x && x < n && 0 <= y && y < m) return true;
    
    return false;
}

int bfs() {
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++) { 
            d[i][j] = INF;
        }
    }
    
    P s = getStartOrGoal('S');
    P g = getStartOrGoal('G');
    
    queue<P> que;
    que.push(s);
    d[s.first][s.second] = 0;
    
    while (que.size()) {
        P p = que.front();
        que.pop();
        
        if (p == g) break;
        
        for (int i = 0; i < 4; i++) {
            int nx = p.first + dx[i];
            int ny = p.second + dy[i];
            P n  = P(nx, ny);
            
            if (inMaze(p) && maze[nx][ny] != '#' && d[nx][ny] == INF) {
                que.push(n);
                d[nx][ny] = d[p.first][p.second] + 1;
            }
        }
    }
    return d[g.first][g.second];
}

int main() {
    int ans = bfs();
    printf("%d\n", ans);
    return 0;
}

