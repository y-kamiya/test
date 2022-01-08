#include <iostream>
using namespace std;

int main() {
    char a[3];
    cin >> a;

    int count = 0;
    for (int i = 0; i < 3; ++i) {
        if (a[i] == '1') {
            ++count;
        }
    }
    cout << count << endl;

    return 0;
}
