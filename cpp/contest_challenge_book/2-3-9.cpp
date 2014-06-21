/*
 * トラック
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

const int N = 4;
const int L = 25;
const int P = 10;
int A[N] = {10,14,20,21};
int B[N] = {10,5,2,4};

int solve() {
    int l = 0, p = P;
    int count = 0;
    priority_queue<int> pque;

    for (int i = 0; i < N; i++) {
        int d = A[i] - l;
        while (p - d < 0) {
            if (pque.empty()) {
                return -1;;
            }
            p += pque.top();
            pque.pop();
            count++;
        }
        p -= d;
        l = A[i];
        pque.push(B[i]);
    }
    return count;
}

int main() {
    int count = solve();
    cout << count << endl;
    return 0;
}

