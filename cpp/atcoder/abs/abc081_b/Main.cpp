#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int a[n];
    for (int i = 0; i < n; ++i) cin >> a[i];

    int count = 0;
    bool check = true;
    while (true) {
        for (int i = 0; i < n; ++i) {
            if (a[i] % 2 != 0) {
                check = false;
                break;
            }
            a[i] /= 2;
        }

        if (!check) {
            break;
        }

        ++count;
    }

    cout << count << endl;

    return 0;
}

