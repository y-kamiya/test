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



int N;
string S;

void _main() {
    cin >> N >> S;

    list<int> A{0};

    auto it = A.begin();

    REP(i, N) {
        // std::for_each(A.cbegin(), A.cend(), [](int x){
        //     cout << x << " ";
        // });
        // cout << endl;


        if (S[i] == 'L') {
            A.insert(it, i+1);
            --it;
        } else {
            A.insert(next(it), i+1);
            ++it;
        }
    }

    std::for_each(A.cbegin(), A.cend(), [](int x){
        cout << x << " ";
    });
    cout << endl;
}

int main() {
    _main();
    return 0;
}

