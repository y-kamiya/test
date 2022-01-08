#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N, Y;
    cin >> N >> Y;

    for (int i = 0; i < N + 1; ++i) {
        for (int j = i; j < N + 1; ++j) {
            int sum = 10000 * i + 5000 * (j - i) + 1000 * (N - j);
            if (sum == Y) {
                cout << i << " " << (j - i) << " " << N - j << endl;
                return 0;
            }
        }
    }

    cout << -1 << " " << -1 << " " << -1 << endl;

    return 0;
}
