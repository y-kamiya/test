#include <iostream>
using namespace std;

int H, W;
string map[50];
int X[8] = {1, 1, 1, 0, -1, -1, -1, 0};
int Y[8] = {-1, 0, 1, 1, 1, 0, -1, -1};

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

    char result[H][W];

    // cout << isBomb(4, 1) << endl;
    // return 0;
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (map[i][j] == '#') {
                result[i][j] = '#';
                continue;
            }

            int num = 0;
            for (int k = 0; k < 8; ++k) {
                int x = j + X[k];
                int y = i + Y[k];
                num += static_cast<int>(isBomb(x, y));
            }

            result[i][j] = to_string(num).c_str()[0];
        }
    }

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            cout << result[i][j];
        }
        cout << endl;
    }

    return 0;
}
