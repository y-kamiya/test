/*
 * union find
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

const int _MAX_ELEM = 100;

class UnionFind {
    int par[_MAX_ELEM];
    int rank[_MAX_ELEM];

public:
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
};

/*
int main() {
    init(10);
    cout << find(2) << endl;
    cout << same(2,3) << endl;
    unite(2, 3);
    cout << find(2) << endl;
    cout << find(3) << endl;
    cout << same(2,3) << endl;
    return 0;
}
*/

