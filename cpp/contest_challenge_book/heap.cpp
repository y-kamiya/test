/*
 * heap
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

class Heap 
{
    int sz;
    int heap[100];
public:
    void push(int x) {
        int i = sz++;
        while (i > 0) {
            cout << i << endl;
            int p = (i - 1) / 2;
            if (heap[p] <= x) break;
            heap[i] = heap[p];
            i = p;
        } 
        heap[i] = x;
    }
    int pop() {
        int ret = heap[0];
        int x = heap[--sz];
        int i = 0;
        while (i * 2 + 1 < sz) {
            int a = i * 2 + 1, b = i * 2 + 2;
            if (b < sz && heap[b] < heap[a]) a = b;
            if (heap[a] >= x) break;
            heap[i] = heap[a];
            i = a;
        }
        heap[i] = x;
        return ret;
    }
};

int main() {
    Heap h;
    for (int i = 0; i < 10; i++) {
        h.push(i);
    }
    for (int i = 0; i < 10; i++) {
        printf("%d ", h.pop());
    }
    return 0;
}

