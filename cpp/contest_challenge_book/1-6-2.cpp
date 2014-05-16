#include <cstdio>
#include <algorithm>

using namespace std;

#define L 10
#define N 5
int a[N] = {2,3,4,5,10};

int main() {
    sort(a, a + N);

    int minimum = 0, maximum = 0;
    for (int i = 0; i < N; i++) {
        if (a[i] < L/2) {
            minimum = max(a[i], minimum);
        } else {
            minimum = max(L - a[i], minimum);
        }
    }
    printf("%d\n", minimum);

    for (int j = 0; j < N; j++) {
        if (a[j] < L/2) {
            maximum = max(L - a[j], maximum);
        } else {
            maximum = max(a[j], maximum);
        }
    }
    printf("%d\n", maximum);
}

