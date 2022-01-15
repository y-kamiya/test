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

string s;

int num(int a, int b, int c) {
    return 100 * a + 10 * b + c;
}

int main() {
    cin >> s;

    int a = s[0] - '0';
    int b = s[1] - '0';
    int c = s[2] - '0';

    int sum = num(a, b, c) + num(b, c, a) + num(c, a, b);
    cout << sum << endl;
    return 0;
}

// 21:04
