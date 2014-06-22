/*
 * グラフ生成（隣接リスト）
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>

#define ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))

using namespace std;

int G[][3] = {
    {0,1,1},
    {1,0,1},
    {1,1,0},
};

template<int SIZE> class Graph {
public:
    int v;
    int g[SIZE][SIZE];
public:
    Graph(int g[][SIZE]) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                this->g[i][j] = g[i][j];
            }
        }
        this->v = SIZE;
    }

};


int main() {
    Graph<ARRAY_LENGTH(G)> *graph = new Graph<ARRAY_LENGTH(G)>(G);
    cout << (graph->g[0][1]) << endl;
    delete graph;
    
    return 0;
}

