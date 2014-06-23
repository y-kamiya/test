/*
 * cable master
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
typedef vector<double> V;

V data;


int getNum(double l, V data) 
{
    int count = 0;
    for (V::iterator it = data.begin(); it != data.end(); it++) {
        count += (*it) / l;
    }
    return count;

}

double solve(int n, int k, V data) 
{
    double lb = 0, ub = *max_element(data.begin(), data.end());

    while (ub - lb > 0.01) {
        double l = (ub + lb) / 2;
        cout << lb << " " << ub << " " << l << endl;
        if (getNum(l, data) >= k) {
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
    double a;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &a);
        data.push_back(a);
    }
    double res = solve(n, k, data);
    printf("%.2f\n", res);
    return 0;
}

