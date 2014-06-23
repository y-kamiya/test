/*
 * face the right way
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>
#include <set>

#define INF 1000000

using namespace std;

typedef long long ll;
typedef vector<int> V;


int solve(int n, int k, string s) 
{
    int count = 0;
    for (int i = 0; i + k <= n; i++) {
        if (s[i] == 'F') continue;
        count++;
        for (int j = i; j < i + k; j++) {
            if (s[j] == 'F') {
                s[j] = 'B';
            } else {
                s[j] = 'F';
            }
        }
    }
    cout << "K = " << k << " " << "M = " << count << "   " << s << endl;
    for (int i = n - 1; i >= n - k; i--) {
        if (s[i] != 'F') return INF;
    }
    return count;
}

int solve2(int n, int k, string s) 
{
    int f[n];
    memset(f, 0, sizeof(f));

    int dir[n];
    for (int i = 0; i < n; i++) {
        if (s[i] == 'F') dir[i] = 0;
        else dir[i] = 1;
    }

    int res = 0, sum = 0;
    for (int i = 0; i + k <= n; i++) {
        if ((dir[i] + sum) % 2 != 0) {
            res++;
            f[i] = 1;
        }
        sum += f[i];
        if (i - k + 1 >= 0) {
            sum -= f[i - k + 1];
        }
    }

    for (int i = n - k + 1; i < n; i++) {
        if ((dir[i] + sum) % 2 != 0) {
            return -1;
        }
    }
    return res;
}

int main() 
{
    int n;
    scanf("%d", &n);
    string s;
    cin >> s;

    int K = 0, M = INF;
    for (int k = 1; k < n; k++) {
        int count = solve(n, k, s);
        if (count < M) {
            K = k;
            M = count;
        }
    }
    printf("K = %d, M = %d\n", K, M);
    return 0;
}

