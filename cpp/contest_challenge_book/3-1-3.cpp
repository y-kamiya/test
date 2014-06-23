/*
 * aggressive cows
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


bool C(int l, int k, V data) 
{
    int count = 0, x = -INF;
    for (V::iterator it = data.begin(); it != data.end(); it++) {
        if (x + l <= (*it)) {
            count++;
            x = *it;
        }
    }
    return count >= k;

}

int solve(int n, int k, V data) 
{
    int lb = 0, ub = INF;
    sort(data.begin(), data.end());

    while (ub - lb > 1) {
        int l = (ub + lb) / 2;
        cout << lb << " " << ub << " " << l << endl;
        if (C(l, k, data)) {
            lb = l;
        } else {
            ub = l;
        }
    }
    return lb;
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
    int res = solve(n, k, data);
    printf("%d\n", res);
    return 0;
}

