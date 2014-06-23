/*
 * subsequence
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>

#define INF 1000000

using namespace std;

typedef long long ll;
typedef vector<int> V;

V data;


int sum(int s, int t, V data) 
{
    int res = 0;
    for (int i = s; i <= t; i++) {
        res += data[i];
    }
    return res;
}

int solve(int n, int k, V data) 
{
    int res = INF;
    for (int i = 0; i < n; i++) {
        int lb = i, ub = n-1;
        while (ub - lb > 1) {
            int mid = (lb + ub) / 2;
            if (sum(i, mid, data) >= k) {
                ub = mid;
            } else {
                lb = mid;
            }
        }
        if (sum(i, ub, data) >= k) {
            res = min(res, ub - i + 1);
        }
    }

    return res;
}

int solve2(int n, int k, V data) 
{
    int res = n + 1;
    int s, t, sum;
    s = t = sum = 0;
    while (true) {
        while (t < n && sum < k) {
            sum += data[t++];
        }
        if (sum < k) break;

        res = min(res, t - s);
        sum -= data[s++];
    }

    if (res > n) {
        return 0;
    }
    return res;
}


int main() 
{
    int n, k;
    int a;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        data.push_back(a);
    }
    int res = solve2(n, k, data);
    printf("%d\n", res);
    return 0;
}

