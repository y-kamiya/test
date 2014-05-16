#include <cstdio>
#include <algorithm>

using namespace std;

typedef pair<int, int> P;

const int n = 5;
const int m = 6;
const int INF = 100000000;
char maze[n][m+1] = {
    "#S####",
    ".....#",
    ".##.##",
    "#....#",
    "#G####",
};

int d[n][m+1];
int dx[4] = {1,0,-1,0}; dy[4] = {0,1,0,-1};


void dfs(int x, int y) {
    field[x][y] = '.';

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            int nx = x + dx, ny = y + dy;
            if (0 <= nx && nx < n && 
                0 <= ny && ny < m && 
                field[nx][ny] == 'W') {

                dfs(nx, ny);
            }
        }
    }
    return;

}

int main() {
    int res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (field[i][j] == 'W') {
                dfs(i, j);
                res++;
            }
        }
    }
    printf("%d\n", res);
    return 0;
}

