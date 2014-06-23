/*
 * lower bound
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

vector<int> data;

int solve(int n, int k, vector<int> data) 
{
    int lb = -1, ub = n;

    while (ub - lb > 1) {
        int mid = (lb + ub) / 2;
        if (data[mid] >= k) {
            ub = mid;
        } else {
            lb = mid;
        }
    }
    return ub;
}

int main() 
{
    int n, k, a;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        data.push_back(a);
    }
    int res = solve(n, k, data);
    printf("%d\n", res);
    return 0;
}

