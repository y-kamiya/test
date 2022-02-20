#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define REP(i,n) for(int i=0, i##_len=(n); i<i##_len; ++i)
#define REPR(i,n) for(int i=n;i>=0;i--)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define FORR(i,a,b) for(int i=(a);i>=(b);--i)
#define ALL(x) (x).begin(),(x).end()
#define UNIQUE(v) v.erase( unique(v.begin(), v.end()), v.end() );
#define YES(n) cout << ((n) ? "YES" : "NO"  ) << endl
#define Yes(n) cout << ((n) ? "Yes" : "No"  ) << endl
#define PRINT_DOUBLE(n, x) cout << std::fixed << std::setprecision(n) << x << endl;

using P = pair<int, int>;

void _main() {
    int N, X;
    cin >> N >> X;

    int a[N], b[N];
    int min_sum = 0;
    int max_sum = 0;
    REP(i, N) {
        cin >> a[i] >> b[i];
        min_sum += a[i];
        max_sum += b[i];
    }
    if (min_sum > X) {
        Yes(0);
        return;
    }
    if (max_sum < X) {
        Yes(0);
        return;
    }
    if (min_sum == X || max_sum == X)  {
        Yes(1);
        return;
    }

    queue<P> que;
    que.emplace(0, 0);
    while (!que.empty()) {
        P p = que.front();

        int i = p.first;
        int d = p.second;
        // cout << "i: " << i << ", d: " << d << endl;
        if (i >= N) break;
        que.pop();

        int next = d + a[i];
        if (X <= (N-i-1) * 100 + next && next <= X) {
            // cout << "a: " << d + a[i] << endl;
            que.emplace(i+1, next);
        }

        next = d + b[i];
        if (X <= (N-i-1) * 100 + next && next <= X) {
            // cout << "b: " << d + b[i] << endl;
            que.emplace(i+1, next);
        }
    }

    while (!que.empty()) {
        P p = que.front();
        que.pop();
        // cout << p.first << " " << p.second << endl;
        if (p.second == X) {
            Yes(1);
            return;
        }
    }
    Yes(0);
}

int main() {
    _main();
    // cout << "=============== " << endl;
    // _main();
    // cout << "=============== " << endl;
    // _main();
    return 0;
}

