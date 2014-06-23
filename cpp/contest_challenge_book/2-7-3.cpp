/*
 * Bribe the prisoners
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

int solve(int a, int b, vector<int> data) 
{
    if (data.empty()) return 0;
    cout << a << ", " << b << ":  ";
    for (int k = 0; k < (int)data.size(); k++) {
        cout << data[k] << " ";
    }
    cout << endl << endl;

    int res = INF;
    int q = data.size();
    for (int i = 0; i < q; i++) {
        int release = data[i];
        vector<int> left, right;
        for (int j = 0; j < q; j++) {
            if (j == i) continue;
            if (j < i) left.push_back(data[j]);
            else right.push_back(data[j]);
        }
        res = min(res,  b-a + solve(a, release-1, left) + solve(release+1, b, right));
    }
    return res;
}

int main() 
{
    int p, q, a;
    scanf("%d %d", &p, &q);
    for (int i = 0; i < q; i++) {
        scanf("%d", &a);
        data.push_back(a);
    }
    int res = solve(1, p, data);
    printf("%d\n", res);
    return 0;
}

