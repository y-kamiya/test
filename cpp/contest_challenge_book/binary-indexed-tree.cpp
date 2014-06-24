/*
 * binary indexed tree
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

const int n = 8;
int bit[n+1];

int sum(int i)
{
    int s = 0;
    while (i > 0) {
        s += bit[i];
        i -= i & -i;
    }
    return s;
}

void add(int i, int x)
{
    while (i <= n) {
        bit[i] += x;
        i += i & -i;
    }
}

int main() 
{
    int a[n] = {5,3,7,9,6,4,1,2};
    for (int i = 1; i <= n; i++) {
        add(i, a[i-1]);
    }
    for (int i = 1; i <= n; i++) {
        cout << bit[i] << ", ";
    }
    cout << endl;

    cout << sum(2) << endl;
    add(2, 1);
    cout << sum(2) << endl;
    cout << sum(4) << endl;



}


