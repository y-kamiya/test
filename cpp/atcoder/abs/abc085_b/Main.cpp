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

    sort(a.begin(), a.end());
    a.erase(std::unique(a.begin(), a.end()), a.end());

    cout << a.size() << endl;

    return 0;
}
