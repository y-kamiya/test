/*
 * heap
 */
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

class Heap 
{
private:
    vector<int> heap;
public:
    void push(int x) {
    }
    int pop() {
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

