#include <bits/stdc++.h>
#include <string>
using namespace std;

using ll = long long;

#define REP(i,n) for(int i=0, i##_len=(n); i<i##_len; ++i)
#define REPR(i,n) for(int i=n;i>=0;i--)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define ALL(x) (x).begin(),(x).end()
#define UNIQUE(v) v.erase( unique(v.begin(), v.end()), v.end() );
#define YES(n) cout << ((n) ? "YES" : "NO"  ) << endl
#define Yes(n) cout << ((n) ? "Yes" : "No"  ) << endl

int N, Q;
int a[200005];
int x[200005];
int k[200005];

size_t toHash(int x, int k) {
    string s = to_string(x) + "@" + to_string(k);
    return std::hash<string>()(s);
}

int main() {
    cin >> N >> Q;
    REP(i, N) cin >> a[i];
    REP(i, Q) {
        cin >> x[i];
        cin >> k[i];
    }

    unordered_map<int, int> cntMap;
    unordered_map<size_t, int> queryMap;
    FOR(i, 0, N) {
        int kk = 1;
        if (cntMap.count(a[i]) != 0) {
            kk = cntMap[a[i]] + 1;
        }
        cntMap[a[i]] = kk;

        size_t h = toHash(a[i], kk);
        queryMap[h] = i + 1;
    }

    FOR(i, 0, Q) {
        size_t h = toHash(x[i], k[i]);
        if (queryMap.count(h) == 0) {
            cout << -1 << endl;
        } else {
            cout << queryMap[h] << endl;
        }
    }

    return 0;
}

// 21:43
// 21:48
