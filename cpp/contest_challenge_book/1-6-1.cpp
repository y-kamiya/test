#include <cstdio>
#include <algorithm>

using namespace std;

#define N 5
int a[N] = {2,3,4,5,10};

int main() {
    sort(a, a + N);

    int length = 0;
    for (int i = 0; i < N-2; i++) {
        for (int j = i+1; j < N-1; j++) {
            for (int k = j+1; k < N; k++) {
                if (a[k] < a[i] + a[j]) {
                    int l = a[i] + a[j] + a[k]; 
                    length = max(l, length);
                }
            }
        }
    }
    printf("%d\n", length);
}

