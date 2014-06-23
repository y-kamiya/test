/*
 * Crazy Rows
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>

using namespace std;

typedef long long ll;

vector<int> data;

int solve(int n, vector<int> data) 
{
    int res = 0;
    for (int i = 0; i < n; i++) {
        // 現在行が条件をみたすか判定
        int pos = data[i];
        // 満たす→continue
        if (pos <= i) continue;
        // 満たさない
        //  現在行の値が入る行〜最後でループ
        for (int j = i + 1; j < n; j++) {
        //      現在行に入ることができる値を見つけたらそれとswap
            if (data[j] <= i) {
                res += 2 * (j - i) - 1;
                data[i] = data[j];
                data[j] = pos;
            }
        }
    } 
    cout << "data:" << endl;
    for (int i = 0; i < n; i++) {
        cout << data[i] << endl;
    }
    return res;
}

int main() 
{
    int n;
    scanf("%d", &n);
    string s;
    for (int i = 0; i < n; i++) {
      cin >> s;
      data.push_back(s.find_last_of('1'));
    }
    int res = solve(n, data);
    printf("%d\n", res);
    return 0;
}

