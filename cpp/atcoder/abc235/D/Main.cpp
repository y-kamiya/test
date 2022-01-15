#include <bits/stdc++.h>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

using ll = long long;

#define REP(i,n) for(int i=0, i##_len=(n); i<i##_len; ++i)
#define REPR(i,n) for(int i=n;i>=0;i--)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define ALL(x) (x).begin(),(x).end()
#define UNIQUE(v) v.erase( unique(v.begin(), v.end()), v.end() );
#define YES(n) cout << ((n) ? "YES" : "NO"  ) << endl
#define Yes(n) cout << ((n) ? "Yes" : "No"  ) << endl

int a, N;

int digit(ll num) {
    return to_string(num).length();
}

bool canAdd(ll num, const unordered_map<ll, ll>& m) {
    if (1000000 < num) return false;
    if (m.count(num) != 0) return false;
    return true;
}

int main() {
    cin >> a >> N;

    int x = 1;

    unordered_map<ll, ll> history;
    history[x] = 0;

    queue<ll> que;
    que.push(x);

    int digitN = digit(N);

    bool exist = false;
    // REP(i, 1000) {
    while (!que.empty()) {
        x = que.front();
        que.pop();

        // cout << x << endl;
        if (x == N) {
            exist = true;
            break;
        }
        int digitX = digit(x);
        if (digitN < digitX) {
            continue;
        }

        int next1 = x * a;
        if (canAdd(next1, history)) {
            que.push(next1);
            history[next1] = history[x] + 1;
        }

        if (x < 10) continue;;

        string strX = to_string(x);
        if (strX[digitX - 1] == '0') continue;

        string s = strX[digitX-1] + strX.substr(0, digitX-1);
        int next2 = std::stoi(s);
        if (canAdd(next2, history)) {
            que.push(next2);
            history[next2] = history[x] + 1;
        }
    }

    if (exist) {
        cout << history[x] << endl;
    } else {
        cout << -1 << endl;
    }

    return 0;
}


// 22:37
