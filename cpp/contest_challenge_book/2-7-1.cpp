/*
 * Minimum Scalar Product
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>

using namespace std;

typedef long long ll;

vector<int> v1, v2;

int solve(int n, vector<int> v1, vector<int> v2) 
{
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end(), greater<int>());

    ll res = 0;
    for (int i = 0; i < n; i++) {
        res += v1[i] * v2[i];
    }
    return res;
}

int main() 
{
    int n, x, y;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x, &y);
        v1.push_back(x);
        v2.push_back(y);
    }
    int res = solve(n, v1, v2);
    printf("%d\n", res);
    return 0;
}

