#include <iostream>
using namespace std;

int main() {
    int n, a, b;
    cin >> n >> a >> b;

    int total = 0;
    for (int i = 1; i <= n; ++i) {
        string s = to_string(i);
        int sum = 0;
        for (char c : s) {
            int x = c - '0';
            sum += x;
        }

        if (a <= sum && sum <= b) total += i;
    }

    cout << total << endl;

    return 0;
}
