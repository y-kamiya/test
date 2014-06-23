/*
 * fliptile
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


void copy(int n, int m, int **a, int **b)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            b[i][j] = a[i][j];
        }
    }
}

bool isAlphabeticalSmall(int n, int m, int **a, int **b) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] < b[i][j]) return true;
            if (a[i][j] > b[i][j]) return false;
        }
    }
    return true;
}

#define R 5
int x[R] = {0, 0, 1, 0, -1};
int y[R] = {0, 1, 0, -1, 0};

void reverse(int j, int k, int n, int m, int **work) {
    for (int i = 0; i < R; i++) {
        int a = j + x[i], b = k + y[i];
        if (0 <= a && a < m && 0 <= b && b < n) {
            int v = work[a][b];
            work[a][b] = (v + 1) & 1;
        }
    }
}


int solve(int n, int m, int **data) 
{
    int minCount = INF;
    int reverseData[n][m], *r[n], keep[n][m], *k[n];
    int work[n][m], *w[n];

    memset(keep, 1, sizeof(keep));

    for (int i = 0; i < n; i++) {
        k[i] = keep[i];
        r[i] = reverseData[i];
        w[i] = work[i];
    }

    /*
    for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
        cout << a[i][j] << " ";
    }
    cout << endl;
    }
    */
    for (int i = 0; i < 1 << m; i++) {
        memset(reverseData, 0, sizeof(reverseData));
        copy(n, m, data, w);

        // 最初の行を決める
        for (int j = 0; j < m; j++) {
            work[0][m-j-1] = i >> j & 1;
            if (work[0][m-j-1] != data[0][m-j-1]) {
                reverseData[0][m-j-1] = 1;
            }
        }

        int count = 0;
        bool hasBlack = false;
        for (int j = 1; j < n; j++) {
            for (int k = 0; k < m; k++) {
                if (work[j-1][k] == 1) {
                    count++;
                    reverseData[j][k] = 1;
                    reverse(j, k, n, m, w);
                }
                if (j == n - 1 && work[j][k] == 1) {
                    hasBlack = true;
                    break;
                } 
            }
        }

        // 最後の行がすべて0か判定
        if (hasBlack) continue;

        //  ひっくり返した回数を比較
        if (minCount < count) continue;

        if (!isAlphabeticalSmall(n, m, r, k)) continue; 

        //    　countを更新＋現在の状態を保存
        minCount = count;
        copy(n, m, r, data);
    }

    return minCount;
}

int main() 
{
    int n, m;
    scanf("%d %d", &n, &m);

    string s;
    int data[n][m], *d[n];
    for (int i = 0; i < n; i++) {
        cin >> s;
        for (int j = 0; j < m; j++) {
            if (s[j] == '0') data[i][j] = 0;
            else data[i][j] = 1;
        }
        d[i] = data[i];
    }
    int res = solve(n, m, d);
    if (res < INF) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", d[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("IMPOSSIBLE");
    }
    return 0;
}

