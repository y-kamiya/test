#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    sort(a.begin(), a.end(), std::greater<int>{});

    int sum_odd = 0;
    int sum_even = 0;
    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0) {
            sum_even += a[i];
        } else {
            sum_odd += a[i];
        }
    }

    cout << sum_even - sum_odd << endl;

    return 0;
}
