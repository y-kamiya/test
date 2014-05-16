#include <cstdio>
#include <algorithm>

using namespace std;


const int n = 5;
const int k = 100;
const int a[n] = {2,3,4,5,10};

bool dfs(int i, int sum) {
    if (i == n) return sum == k;

    if (dfs(i + 1, sum)) return true;

    if (dfs(i + 1, sum + a[i])) return true;

    return false;
}

int main() {
    if (dfs(0,0)) printf("Yes\n");
    else printf("No\n");
    return 0;
}

