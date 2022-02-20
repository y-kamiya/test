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
    int N;
    cin >> N;

    vector<int> a(N);
    REP(i, N) cin >> a[i];

    vector<P> vec;
    int c = 0;
    int n = 0;
    REP(i, N) {
        if (c == a[i]) {
            ++n;
            if (c == n) {
                if (vec.size() > 0) {
                    auto p = vec[vec.size()-1];
                    vec.pop_back();
                    c = p.first;
                    n = p.second;
                } else {
                    c = 0;
                    n = 0;
                }
            }
        } else {
            if (c != 0) vec.emplace_back(c, n);
            c = a[i];
            n = 1;
        }

        int res = 0;
        for (auto p : vec) {
            // cout << p.first << " " << p.second << endl;
            res += p.second;
        }
        // cout << c << " " << n << " @" << endl;
        cout << res+n << endl;
    }

}

int main() {
    _main();
    // cout << "=============" << endl;
    // _main();
    return 0;
}

