/*
 * 二部グラフ
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

#define MAX_V 3

using namespace std;


vector<int> G[MAX_V];
int color[MAX_V];

bool dfs(int v, int c) {
    color[v] = c;
    for (int i = 0; i < (int)G[v].size(); i++) {
        int col = color[G[v][i]]; 
        if (col == c) return false;
        if (col == 0 && !dfs(G[v][i], -c)) return false;
    }
    return true;
}

int main() {
    int v, e;
    scanf("%d %d", &v, &e);
    for (int i = 0; i < e; i++) {
        int s, t;
        scanf("%d %d", &s, &t);
        G[s].push_back(t);
    }
    for (int i = 0; i < v; i++) {
        if (color[i] == 0) {
            if (!dfs(i, 1)) {
                printf("No\n");
                return 0;
            }
        }
    }
    printf("Yes\n");
    
    return 0;
}

