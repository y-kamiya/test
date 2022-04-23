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
    string S;
    cin >> S;

    bool hasA = false;
    bool hasa = false;

    int size = S.size();
    REP(i, size) {
        FOR(j, i+1, size) {
            if (S[i] == S[j]) {
                Yes(0);
                return;
            }
        }

        int a = S[i] - 'a';
        if (0 <= a && a < 26) hasa = true;

        int A = S[i] - 'A';
        if (0 <= A && A < 26) hasA = true;
    }

    DEBUG(hasa, hasA);

    if (hasa && hasA) Yes(1);
    else Yes(0);
}

int main() {
    _main();
    return 0;
}

