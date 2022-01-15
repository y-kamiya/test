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

int a[4];
string s;

int main() {
    cin >> s;
    REP(i, 4) a[i] = s[i] - '0';

    REP(i, 8) {
        bitset<3> bs(i);
        int sum = a[0];
        string s = to_string(a[0]);
        REP(j, 3) {
            if (bs[j]) {
                sum += a[j+1];
                s.append("+");
            } else {
                sum -= a[j+1];
                s.append("-");
            }
            s.append(to_string(a[j+1]));
        }
        if (sum == 7) {
            cout << s << "=7" << endl;
            return 0;
        }
    }

    cout << "wrong" << endl;;
    return 0;
}




