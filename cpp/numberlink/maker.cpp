#include<cstdio>
#include<cstdlib>
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
#define DEBUG 0
#define TEST 0

#define TRY_MAX 100000

#define N 6
#define M 6

#define NUM 4
int map[N][M] = {};

Point start[NUM];
Point goal[NUM];
/************************ settings *****************************/

// map to represent number of empty point in neighbers 
int mapN[N][M];


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
bool isStart(Point p) {
    for (int i = 1; i <= NUM; i++) {
        if (isStart(i, p)) return true;
    }
    return false;
}
bool isGoal(int num, Point p) {
    return p.x == goal[num-1].x && p.y == goal[num-1].y;
}
bool isGoal(Point p) {
    for (int i = 1; i <= NUM; i++) {
        if (isGoal(i, p)) return true;
    }
    return false;
}


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
    /*
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
    */
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

bool find(int num, Point current) {
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
        return false;
    }


    if (isGoal(num, current)) {
        /*
        printMap(map, 1, "map");
        printMap(mapN, 1, "mapN");
        */

        // finish checking all NUM
        if (num == NUM) {
            if (zeroIsNotExist()) return true;
            return false;
        }

        int nextNum = ++num;
        bool isFind = find(nextNum, start[nextNum-1]);
        if (isFind) return true;
        return false;
    }
    
    // check next point
    for (int i = 0; i < DIR; i++) {
        Point p = pointSum(current, dir[i]);
#if DEBUG == 1
        //cout << "num:" << num << "\tP(" << p.x << "," << p.y << ")\t" << isVerbose(num, p) << endl;
#endif
        if (isVerbose(num, p)) continue;
        if (isGoal(num, p) || (inMap(p) && isEmpty(p))) {
            bool isFind = find(num, p);
            if (isFind) return true;
        }
    }
    fs << "back(no more dir)" << endl;
    back(num, current);

    return false;
    
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

bool solve() {
    setStartAndGoal();
    setMapN();

    /*
    printMap(map, 3, "map");
    printf("=========================================\n");
    fs << "==========================================" << endl;
    */

    return find(1, start[0]);
}

void shuffle(int array[], int size) {
    srand((unsigned) time(NULL));
    for (int i = 0; i < size; i++) {
        int j = rand() % size;
        int tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }
}

int main() {
#if TEST == 1
    testIsVerbose();
    return 0; 
#endif    
    
    int array[N*M] = {};
    for (int num = 1; num <= NUM; num++) {
        array[2 * num] = num;
        array[2 * num + 1] = num;
    }

    clock_t starttime = clock();
    int i;
    for (i = 0; i < TRY_MAX; i++) {
        shuffle(array, N*M);

        /*
        int a[N][M] = {
            {1,0,0,0},
            {0,0,3,0},
            {0,2,0,2},
            {0,1,0,3},
        };
        */
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                map[i][j] = array[M * i + j];
                //map[i][j] = a[i][j];
                //cout << map[i][j] << " ";
            }
            //cout << endl;
        }
        if (solve()) {
            int problem[N][M] = {};
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    int num = map[i][j], count = 0;
                    Point p = {i, j};
                    for (int k = 0; k < DIR; k++) {
                        Point pp = pointSum(p, dir[k]);
                        if (inMap(pp) && map[pp.x][pp.y] == num) count++;
                    }
                    if (count == 1) {
                        problem[i][j] = num;
                    }
                }
            }
            
            printMap(problem, 2, "created problem\n");
#if DEBUG == 1
            printMap(map, 2, "answer\n");
#endif
            break;
        }
    }
    if (i == TRY_MAX) {
        cout << "fail to create problem" << endl;
    }
    clock_t endtime = clock();
    cout << "time: " << (endtime - starttime) / 1000  << " [ms]" << endl;

    return 0;
}

