/*
 * Bribe the prisoners (dp)
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>

#define INF 1000000
#define P 20
#define Q 3

using namespace std;

typedef long long ll;

int data[Q+2];
int dp[Q+1][Q+2];

void solve() 
{
    data[0] = 0;
    data[Q+1] = P + 1;

    for (int i = 0; i < Q; i++) {
        dp[i][i+1] = 0;
    }

    for (int w = 2; w <= Q + 1; w++) {
        for (int i = 0; i + w <= Q + 1; i++) {
            int j = i + w, t = INF;

            for (int k = i + 1; k < j; k++) {
                t = min(t, dp[i][k] + dp[k][j]);
            }
            dp[i][j] = t + data[j] - data[i] - 2;
        }

    }

    for (int i = 0; i < Q+1; i++) {
        for (int j = 0; j < Q+2; j++) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() 
{
    int p, q, a;
    scanf("%d %d", &p, &q);
    for (int i = 1; i <= q; i++) {
        scanf("%d", &a);
        data[i] = a;
    }
    solve();
    printf("%d\n", dp[0][q+1]);
    return 0;
}

