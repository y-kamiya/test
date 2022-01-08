#include <iostream>
using namespace std;

int main() {
    string S;
    cin >> S;

    string ss[4] = {"dream", "dreamer", "erase", "eraser"};
    
    while (true) {
        bool finished = true;
        for (int i = 0; i < 4; ++i) {
            int index = S.size() - ss[i].size();
            if (index < 0) {
                continue;
            }

            string sub = S.substr(index);
            if (sub == ss[i]) {
                if (index == 0) {
                    cout << "YES" << endl;
                    return 0;
                }
                S = S.substr(0, index);
                finished = false;
                break;
            }
        }
        if (finished) {
            cout << "NO" << endl;
            return 0;
        }
    }

    return 0;
}

