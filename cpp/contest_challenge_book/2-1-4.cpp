#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

const int N = 6;
const int R = 10;
int X[N] = {1,7,15,20,30,41};


int main() {
    sort(X, X + N);

    int i = 0;
    vector<int> marks;
    while (i < N) {
        int xi = X[i];
        while (i < N && X[i] <= xi + R) i++; 
        int p = X[i-1];
        while (i < N && X[i] <= p + R) i++; 
        marks.push_back(p);
    }
    printf("size: %zd\n", marks.size());
    for (int j = 0; j < (int)marks.size(); j++) {
        printf("%d, ", marks[j]);
    }
    printf("\n");
    return 0;
}

