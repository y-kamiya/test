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


int A,B,C,D;

bool isPrime(int n) {
    int sqrtN = sqrt(n);
    FOR(i, 2, sqrtN+1) {
        if (n % i == 0) return false;
    }
    return true;
}

void _main() {
    cin >> A >> B >> C >> D;

    FOR(i, A, B+1) {
        vector<int> primes;
        FOR(j, C, D+1) {
            if (isPrime(i+j)) primes.push_back(1);
            else primes.push_back(0);
        }

        int sum = 0;
        for (auto v : primes) sum += v;
        if (sum == 0) {
            cout << "Takahashi" << endl;
            return;
        }
    }

    cout << "Aoki" << endl;

}

int main() {
    _main();
    return 0;
}

// 21:45

