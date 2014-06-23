/*
 * Jessica' reading problem
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

V data;


int solve(int n, V data) 
{
    int s = 0, t = 0, res = n + 1;
    set<int> all(data.begin(), data.end()), current;
    while (true) {
        while (t < n && all != current) {
            current.insert(data[t++]);
        }
        if (all != current) break;

        cout << t << " " << s << endl;
        res = min(res, t - s);
        current.erase(data[s++]);
    }
    return res;
}


int main() 
{
    int n;
    int a;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        data.push_back(a);
    }
    int res = solve(n, data);
    printf("%d\n", res);
    return 0;
}

