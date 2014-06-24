/*
 * ドミノ敷き詰め
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>
#include <set>

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

#define INF 1000000

using namespace std;

typedef long long ll;
typedef vector<int> V;

const int n = 5, m = 5;
int A[n][m] = {
    {0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
};


int solve(int l, int a[][m])
{
    int y = l / m, x = l % m, res = 0;
    if (x == n-1 && y == m-1) {
        if (a[x][y] == 1) {
            return 1;
        } else {
            return 0;
        }
    }
    if (a[x][y] == 1) {
        return solve(l+1, a);
    }

    cout << x << ", " << y << endl;
    int b[n][m], c[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            b[i][j] = a[i][j];
            c[i][j] = a[i][j];
        }
    }

    if (x + 1 < m && a[x+1][y] != 1) {
        b[x][y] = 1;
        b[x+1][y] = 1;
        res += solve(l+1, b);
    }
    if (y + 1 < n && a[x][y+1] != 1) {
        c[x][y] = 1;
        c[x][y+1] = 1;
        res += solve(l+1, c); 
    }
    return res;
}

int dp[2][1 << m];
bool color[n][m];

void solve2() 
{
    int *crt = dp[0], *next = dp[1];
    crt[0] = 1;
    for (int i = n-1; i >= 0; i--) {
        for (int j = m-1; j >= 0; j--) {
            for (int used = 0; used < 1 << m; used++) {
                if ((used >> j & 1) || color[i][j]) {
                    next[used] = crt[used & ~(1 << j)];
                }
            }
        }
    }


}

int main() 
{
    int res = solve(0, A);
    printf("%d\n", res);
}
