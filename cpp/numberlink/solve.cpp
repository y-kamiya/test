#include<cstdio>
#include<iostream>
#include<fstream>
#include<string>
#include<ctime>

using namespace std;

// log file
ofstream fs("log");

struct Point {
    int x;
    int y;
};

// direction to move
#define DIR 4
Point dir[4] = {{-1,0}, {0,1}, {1,0}, {0,-1}};


/************************ settings *****************************/
#define DEBUG 1

#define N 8
#define M 8

#if N == 4
#define NUM 3
int map[N][M] = {
    {1,0,0,0},
    {0,0,3,0},
    {0,2,0,2},
    {0,1,0,3},
};

#elif N == 7
#define NUM 4
int map[N][M] = {
    {0,0,0,0,0,0,2},
    {0,0,0,0,0,0,0},
    {0,0,3,0,0,0,0},
    {2,0,0,0,1,0,0},
    {0,0,0,0,0,0,0},
    {3,4,0,0,0,4,0},
    {1,0,0,0,0,0,0},
};

#elif N == 8
#define NUM 4
int map[N][M] = {
    {0,0,0,0,0,0,0,4},
    {0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,4,0},
    {0,0,0,0,0,0,0,0},
    {0,3,0,0,0,0,0,0},
    {0,0,0,0,0,0,2,0},
    {0,0,3,0,0,0,0,0},
    {1,0,0,0,0,0,0,2},
};

#elif N == 9
#define NUM 4
int map[N][M] = {
    {0,0,0,0,0,0,0,0,3},
    {0,0,0,0,0,0,0,0,1},
    {0,0,0,0,2,0,0,0,0},
    {0,0,0,0,3,0,0,0,0},
    {0,0,0,0,2,0,0,0,0},
    {0,0,0,0,0,4,0,0,0},
    {0,4,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0,0},
};
#endif

Point start[NUM];
Point goal[NUM];
/************************ settings *****************************/



void setStartAndGoal() {
    bool alreadySetStart[NUM+1] = {};
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int num = map[i][j];
            if (num == 0) continue;
            Point p = {i, j};
            if (alreadySetStart[num] == true) {
                goal[num-1] = p;
            } else {
                alreadySetStart[num] = true;
                start[num-1] = p;
            }
        }
    }
#if DEBUG == 1
    for (int i = 0; i < NUM; i++) {
        cout << "start " << i << ": (" << start[i].x << "," << start[i].y << ")\t" << "goal " << i << ": (" << goal[i].x << "," << goal[i].y << ")" << endl;
    }

#endif
}

void printMap(int p[][N], int output) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (output == 1 || output == 3) { fs << map[i][j] << " "; }
            if (output == 2 || output == 3) { printf("%d ", map[i][j]); }
        }
        if (output == 1 || output == 3) { fs << endl; }
        if (output == 2 || output == 3) { printf("\n"); }
    }
}

void logPoint(int num, Point p) {
    fs << "num:" << num << "\tcurrent: (" << p.x << "," << p.y << ")" << endl;
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
bool zeroIsNotExist() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (map[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

void setNumToMap(int num, Point p) {
    map[p.x][p.y] = num;
}
    

void find(int num, Point current) {
#if DEBUG == 1
    logPoint(num, current);
#endif
    setNumToMap(num, current);
    if (isGoal(num, current)) {
        printMap(map, 1);
        if (num == NUM && zeroIsNotExist()) {
            printMap(map, 2);
            return;
        }
        int nextNum = ++num;
        find(nextNum, start[nextNum-1]);
        return;
    }
    for (int i = 0; i < DIR; i++) {
        Point p = pointSum(current, dir[i]);
#if DEBUG == 1
        //cout << "num:" << num << "\tP(" << p.x << "," << p.y << ")\t" << isVerbose(num, p) << endl;
#endif
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

    clock_t starttime = clock();
    setStartAndGoal();
    printMap(map, 3);
    printf("=========================================\n");
    fs << "==========================================" << endl;

    find(1, start[0]);
    clock_t endtime = clock();
    cout << "time: " << (endtime - starttime) / 1000  << " [ms]" << endl;
    return 0;
}

