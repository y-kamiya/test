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

static const int MAX = 5;
int n;
int A[MAX][MAX], B[MAX][MAX];
int X[MAX][MAX], Y[MAX][MAX];

ll conv(int l, int r, int t, int b, int X[][MAX], int Y[][MAX]) {
    ll sum = 0;
    FOR(i, t, b+1) {
        FOR(j, l, r+1) {
            sum += X[i][j] * Y[i][j];
        }
    }
    return sum;
}

ll calc(int X[][MAX], int Y[][MAX]) {
    ll m = 0;
    FOR(h, 0, MAX) {
        FOR(w, 0, MAX) {
            FOR(l, 0, MAX) {
                FOR(t, 0, MAX) {
                    m = max(m, conv(l, l+h, t, t+w, X, Y));
                }
            }
        }
    }
    return m;
}

void rotate90(int k, int X[][MAX], int n) {
    int Y[n][n];
    REP(i, n) REP(j, n) Y[i][j] = X[i][j];

    REP(i, n) REP(j, n) X[i][j] = Y[n-j-1][i];

    // if (k == 1) {
    //     REP(i, n) REP(j, n) X[i][j] = Y[n-j-1][i];
    // } else if (k == 2) {
    //     REP(i, n) REP(j, n) X[i][j] = Y[n-i-1][n-j-1];
    // } else if (k == 3) {
    //     REP(i, n) REP(j, n) X[i][j] = Y[j][n-i-1];
    // }
}

void _main() {
    cin >> n;

    REP(i, n) REP(j, n) cin >> A[i][j];
    REP(i, n) REP(j, n) cin >> B[i][j];


    ll m = 0;
    REP(i, 4) {
        // cout << "-----------------------" << endl;
        REP(j, 1) {
            // Aをi回90°回転
            if (i != 0) rotate90(i, A, n);
            // REP(i, n) {
            //     REP(j, n) cout << A[i][j] << ", ";
            //     cout << endl;
            // }
            
            // 各部分長方形の積和計算してmaxを返す
            m = max(m, calc(A, B));
        }
    }

    cout << m << endl;
}

int main() {
    _main();
    cout << "-----------------------" << endl;
    _main();
    cout << "-----------------------" << endl;
    _main();
    cout << "-----------------------" << endl;
    _main();
    return 0;
}


/*
5x5
1: 25
2: 4*5*2 = 40
3: 3*5*2 = 30
4: 2*5*2 + 4*4 = 36
5: 1*5*2 = 10
6: 3*2*2 = 12

9: 3*3 = 9




回し方
4 * 4 = 16


500 * 16 = 9000

最大25回の積和
*/

/*
部分長方形を2マス分で取り出した場合のパターン数が最大となり40パターン(1x2, 2x1で各部分から取り出すので)
1パターンあたり積和の計算が最も多くなるのは5x5全体を部分長方形とした場合であり、積25回 + 和24回で50回程度
マスは5x5=25マスなので長方形にならない場合も含めてしまうと、部分長方形のマス数は25通り
よって過剰に計算した場合でも最大の積和回数は
40パターン x 50回 x 25 = 50000

元のA, Bを時計回りに90度ずつ任意回数回せるための組み合わせは4x4=16通り
よって全探索した場合の積和回数は100万回には収まると考えられる
*/
