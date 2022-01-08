#include <iostream>
using namespace std;

int main() {
    int N;
    cin >> N;

    int T[N+1];
    int X[N+1];
    int Y[N+1];
    T[0] = X[0] = Y[0] = 0;
    for (int i = 1; i <= N; ++i) {
        cin >> T[i] >> X[i] >> Y[i];
    }
    
    bool canReach = true;
    for (int i = 0; i < N; ++i) {
        int dist = abs(X[i+1] - X[i]) + abs(Y[i+1] - Y[i]);
        int dt = T[i+1] - T[i];
        if (dt < dist) {
            canReach = false;
            break;
        }

        if ((dt - dist) % 2 != 0) {
            canReach = false;
            break;
        }
    }

    if (canReach) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}
