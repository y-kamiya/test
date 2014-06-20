#include<cstdio>
#include<iostream>
#include<string>

#define N 4
#define M 4
#define NUM 3
#define DIR 4



using namespace std;

struct Point {
    int x;
    int y;
};

int map[N][M] = {
    {1,0,0,0},
    {0,0,3,0},
    {0,2,0,2},
    {0,1,0,3},
};

Point start[NUM] = {{0,0}, {2,1}, {1,2}};
Point goal[NUM]  = {{3,1}, {2,3}, {3,3}};
Point dir[4]     = {{-1,0}, {0,1}, {1,0}, {0,-1}};

void printMap(int p[][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
}

void printPoint(Point p) {
    printf("current: (%d,%d)\n", p.x, p.y); 
}

Point pointSum(Point a, Point b) {
    Point p = {a.x + b.x, a.y + b.y};
    return p;
}

bool inMap(Point p) {
    return 0 <= p.x && p.x < N && 0 <= p.y && p.y < M;
}

bool isEmpty(Point p) {
    return map[p.x][p.y] == 0;
}

bool isStart(int num, Point p) {
    return p.x == start[num-1].x && p.y == start[num-1].y;
}
bool isGoal(int num, Point p) {
    return p.x == goal[num-1].x && p.y == goal[num-1].y;
}

bool isVerbose(int num, Point p) {
    int count = 0;
    for (int i = 0; i < DIR; i++) {
        Point pp = pointSum(p, dir[i]);
        if (inMap(pp) && map[pp.x][pp.y] == num && !isGoal(num, pp)) count++;
    }
    if (2 <= count) {
        return true;
    }
    return false;
}

void setNumToMap(int num, Point p) {
    map[p.x][p.y] = num;
}
    

void find(int num, Point current) {
    printPoint(current);
    setNumToMap(num, current);
    if (isGoal(num, current)) {
        printMap(map);
        if (num == NUM) {
            return;
        }
        int nextNum = ++num;
        find(nextNum, start[nextNum-1]);
        return;
    }
    for (int i = 0; i < DIR; i++) {
        Point p = pointSum(current, dir[i]);
        cout << "num:" << num << "\tP(" << p.x << "," << p.y << ")\t" << isVerbose(num, p) << endl;
        if (isVerbose(num, p)) continue;
        if (isGoal(num, p) || (inMap(p) && isEmpty(p))) {
            find(num, p);
        }
    }
    if (!isStart(num, current) && !isGoal(num, current)) {
        setNumToMap(0, current);
    }
    
}

void testPrint(string msg, int num, Point p, int map[][N]) {
    cout << "test false:: " << msg << ", num:" << num << "  P(" << p.x << ", " << p.y << ")" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}

void testIsVerbose() {
    map[0][1] = 1;
    map[1][1] = 1;
    Point p = {1,0};
    if (isVerbose(1, p) == false) { testPrint("isVerbose(1,p)", 1, p, map); }
}

int main() {
    //testIsVerbose();
    printMap(map);
    printf("=========================================\n");

    find(1, start[0]);
    return 0;
}

