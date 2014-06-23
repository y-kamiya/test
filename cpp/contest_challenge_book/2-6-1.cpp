/*
 * 
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;


int gcd(int a, int b) 
{
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() 
{
    int x1 = 5, y1 = 11, x2 = 1, y2 = 3;
    printf("%d\n", gcd(x1-x2, y1-y2) - 1);

    return 0;
}

