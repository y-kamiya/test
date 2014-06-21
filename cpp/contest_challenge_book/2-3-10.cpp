/*
 * 食物連鎖
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

const int N = 100;
int par[N];
int rank[N];

void init(int n) {
    for (int i = 0; i < n; i++) {
        par[i] = i;
        rank[i] = 0;
    }
}

int find(int x) {
    if (par[x] == x) {
        return x;
    } else {
        return par[x] = find(par[x]);
    }
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;

    if (rank[x] < rank[y]) {
        par[x] = y;
    } else {
        par[y] = x;
        if (rank[x] == rank[y]) rank[x]++;
    }
}

bool same(int x, int y) {
    return find(x) == find(y);
}

const int K = 7;
int T[N] = {1,2,2,2,1,2,1};
int X[N] = {101,1,2,3,1,3,5};
int Y[N] = {1,2,3,3,3,1,5};

int solve() {
    init(N * 3);
    int ans = 0;
    for (int i = 0; i < K; i++) {
        int t = T[i];
        int x = X[i] - 1, y = Y[i] - 1;

        if (x < 0 || N <= x || y < 0 || N <= y) {
            ans++;
        }

        if (t == 1) {
            if (same(x,y+N) || same(x,y+2*N)) {
                ans++;
            } else {
                unite(x,y);
                unite(x+N,y+N);
                unite(x+2*N,y+2*N);
            }
        } else {
            if (same(x,y) || same(x,y+2*N)) {
                ans++;
            } else {
                unite(x,y+N);
                unite(x+N,y+2*N);
                unite(x+2*N,y);
            }
        }
    }
    return ans;
}

int main() {
    int count = solve();
    cout << count << endl;
    return 0;
}

