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

void print() { cout << endl; }

template<typename Head, typename... Tail>
void print(Head h, Tail... t) {
    cout << h << " "; print(t...);
}
#ifdef _DEBUG
#define DEBUG(...) print(__VA_ARGS__)
#else
#define DEBUG(...)
#endif


void _main() {
    int N, K;
    cin >> N >> K;

    vector<string> SS(N);
    REP(i, N) cin >> SS[i];

    int ans = 0;
    REP(i, 1<<15) {
        vector<int> count(26, 0);
        REP(j, N) {
            if (i & 1<<j) {
                string s = SS[j];
                REP(k, s.size()) {
                    int c = s[k] - 'a';
                    ++count[c];
                }
            }
        }
        int cnt = 0;
        REP(c, 26) {
            if (count[c] == K) ++cnt;
        }
        ans = max(ans, cnt);
    }

    cout << ans << endl;
}

int main() {
    _main();
    return 0;
}

