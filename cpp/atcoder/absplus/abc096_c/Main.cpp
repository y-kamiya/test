#include <iostream>
using namespace std;

int H, W;
string map[50];
int X[4] = {0, 1, 0, -1};
int Y[4] = {1, 0, -1, 0};

bool isBomb(int x, int y) {
    if (x < 0 || y < 0) {
        return false;
    }
    if (W <= x || H <= y) {
        return false;
    }
    if (map[y][x] == '.') {
        return false;
    }
    return true;
}

int main() {
    cin >> H >> W;
    for (int i = 0; i < H; ++i) cin >> map[i];

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (map[i][j] == '.') continue;

            bool ok = false;
            for (int k = 0; k < 4; ++k) {
                if (isBomb(j + X[k], i + Y[k])) {
                    ok = true;
                    break;
                }
            }

            if (!ok) {
                cout << "No" << endl;
                return 0;
            }
        }
    }

    cout << "Yes" << endl;

    return 0;
}

