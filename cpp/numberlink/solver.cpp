#include<cstdio>
#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<vector>

using namespace std;

// log file
ofstream fs("log");

class Point 
{
public:
    int x, y;
    Point() {}
    Point(int a, int b) {
        this->x = a;
        this->y = b;
    }
    Point operator +(Point p) {
        Point pp = Point(this->x + p.x, this->y + p.y);
        return pp;
    }


};

class Cell {
    int linkCount, value, type;
public:
    enum Type {
        Normal, Start, Goal
    };
    void incLink() {
        this->linkCount++;
    }
    void decLink() {
        this->linkCount--;
    }
    void setValue(int v) {
        this->value = v;
    }
    int getType() {
        return this->type;
    }
    void setType(Type type) {
        this->type = type;
    }
    int getValue() {
        return this->value;
    }
    bool isEmpty() {
        return this->value == 0;
    }

};

typedef vector<vector<Cell> > M;

class Map 
{
    int n, m, maxNum;
    M map;
private:
    int countEmptyAround(Cell cell) {
        int emptyCount = 0;
        Point p = get
        for (int k = 0; k < DIR; k++) {
            Point pp = pointSum(p, dir[k]);
            if (this->inMap(pp) && (cell.isEmpty() || cell.isStart() || cell.isGoal())) emptyCount++;
        }
    }
public:
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                Point p = {i, j};
                int emptyCount = 0;
                for (int k = 0; k < DIR; k++) {
                    Point pp = pointSum(p, dir[k]);
                    if (inMap(pp) && (map[pp.x][pp.y] == 0 || isStart(pp) || isGoal(pp))) emptyCount++;
                }
                mapN[i][j] = emptyCount;
            }
        }
        cout << endl << "mapN" << endl;
        fs << endl << "mapN" << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cout << mapN[i][j] << " ";
                fs << mapN[i][j] << " ";
            }
            cout << endl;
            fs << endl;
        }
    Map() {}
    Map(M map) {
        this->map = map;
        this->n = map.size();
        this->m = map[0].size();
    }
    void init() {
        int maxNum = this->getMaxNum();
        bool alreadySetStart[maxNum+1] = {};

        M::iterator it = this->getBegin();
        for ( ; it != this->getEnd(); it++) {
            for (vector<Cell>::iterator cell = it->begin() ; cell != it->end(); cell++) {
                if (cell->isEmpty()) continue;
                int num = cell->getValue();
                if (alreadySetStart[num]) {
                    cell->setType(Cell::Goal);
                } else {
                    alreadySetStart[num] = true;
                    cell->setType(Cell::Start);
                }
            }
        }
    }
    int getN() {
        return this->n;
    }
    int getM() {
        return this->m;
    }
    int getMaxNum() {
        return this->maxNum;
    }
    Cell getCell(int x, int y) {
        return this->map[x][y];
    }
    M::iterator getBegin() {
        return this->map.begin();
    }
    M::iterator getEnd() {
        return this->map.end();
    }

    bool inMap(Point p) {
        return 0 <= p.x && p.x < this->n && 0 <= p.y && p.y < this->m;
    }

    bool isEmpty(Point p) {
        return this->map[p.x][p.y] == 0;
    }

    bool isStart(int num, Point p) {
        Cell c = this->map[p.x][p.y];
        return c.getType() == Cell::Start;
    }
    bool isStart(Point p) {
        for (int i = 1; i <= this->maxNum; i++) {
            if (isStart(i, p)) return true;
        }
        return false;
    }
    bool isGoal(int num, Point p) {
        Cell c = this->map[p.x][p.y];
        return c.getType() == Cell::Goal;
    }
    bool isGoal(Point p) {
        for (int i = 1; i <= this->maxNum; i++) {
            if (isGoal(i, p)) return true;
        }
        return false;
    }

};


class Solver {
    Map *map;

public:
    Solver(int *map) {
        this->map = map;
        initMap();
    }
    void initMap() {
        this->map->init();
    }

    void setMapN() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                Point p = {i, j};
                int emptyCount = 0;
                for (int k = 0; k < DIR; k++) {
                    Point pp = pointSum(p, dir[k]);
                    if (inMap(pp) && (map[pp.x][pp.y] == 0 || isStart(pp) || isGoal(pp))) emptyCount++;
                }
                mapN[i][j] = emptyCount;
            }
        }
        cout << endl << "mapN" << endl;
        fs << endl << "mapN" << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cout << mapN[i][j] << " ";
                fs << mapN[i][j] << " ";
            }
            cout << endl;
            fs << endl;
        }
    }

    void printMap(int p[][N], int output, string label) {
        if (output == 1 || output == 3) { fs << endl << label << endl; }
        if (output == 2 || output == 3) { cout << endl << label << endl; }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (output == 1 || output == 3) { fs << p[i][j] << " "; }
                if (output == 2 || output == 3) { printf("%d ", p[i][j]); }
            }
            if (output == 1 || output == 3) { fs << endl; }
            if (output == 2 || output == 3) { printf("\n"); }
        }
    }

    void logPoint(int num, Point p) {
        fs << "num:" << num << "\tcurrent: (" << p.x << "," << p.y << ")" << endl;
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
};


// direction to move
#define DIR 4
Point dir[4] = {{-1,0}, {0,1}, {1,0}, {0,-1}};


/************************ settings *****************************/
#define DEBUG 1
#define TEST 0

#define N 9
#define M 9

#if N == 4
#define NUM 2
int map[N][M] = {
    /*
    {1,0,0,0},
    {0,0,3,0},
    {0,2,0,2},
    {0,1,0,3},
    */
    {0,0,0,2},
    {0,1,0,0},
    {0,0,2,0},
    {1,0,0,0},
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

// map to represent number of empty point in neighbers 
int mapN[N][M];



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

bool isNext(Point a, Point b) {
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return dx*dx + dy*dy == 1;

}

bool hasOrphanPoint(Point current) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            Point p = {i, j};
            //fs << "isNext(" << isNext(p,current) << "):: " << i << " " << j << " to " << current.x << " " << current.y << endl;
            if (map[i][j] == 0 && mapN[i][j] <= 1 && !isNext(p, current)) return true;
        }
    }
    return false;
}

void setNumToMap(int num, Point p) {
    map[p.x][p.y] = num;
}

void updateMapN(Point p, bool isRestore) {
    if (map[p.x][p.y] != 0) return;
    for (int i = 0; i < DIR; i++) {
        Point pp = pointSum(p, dir[i]);
        if (inMap(pp)) {
            if (isRestore) {
                mapN[pp.x][pp.y]++;
            } else {
                mapN[pp.x][pp.y]--;
            }
        }
    }

}

void back(int num, Point p) {
    if (!isStart(num, p) && !isGoal(num, p)) {
        setNumToMap(0, p);
        updateMapN(p, true);
    }
}

void find(int num, Point current) {
#if DEBUG == 1
    logPoint(num, current);
#endif
    updateMapN(current, false);
    setNumToMap(num, current);
    /*
    printMap(map, 1, "map");
    printMap(mapN, 1, "mapN");
    */

    // check orphan point
    if (hasOrphanPoint(current)) {
        fs << "back(orphan)" << endl;
        back(num, current);
        return;
    }


    if (isGoal(num, current)) {
        printMap(map, 1, "map");
        printMap(mapN, 1, "mapN");

        // finish checking all NUM
        if (num == NUM) {
            if (zeroIsNotExist()) printMap(map, 2, "map");
            return;
        }

        int nextNum = ++num;
        find(nextNum, start[nextNum-1]);
        return;
    }
    
    // check next point
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
    fs << "back(no more dir)" << endl;
    back(num, current);
    
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

void solve() {
    setStartAndGoal();
    setMapN();

    printMap(map, 3, "map");
    printf("=========================================\n");
    fs << "==========================================" << endl;

    find(1, start[0]);
}

int main() {
#if TEST == 1
    testIsVerbose();
    return 0; 
#endif    

    clock_t starttime = clock();
    solve();
    clock_t endtime = clock();
    cout << "time: " << (endtime - starttime) / 1000  << " [ms]" << endl;

    return 0;
}

