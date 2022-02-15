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


static const int MAX = 55;
int R, C, sy, sx, gy, gx;
char c[MAX][MAX];

using Pos = pair<int,int>;
Pos nextPos[4] = {{1,0},{0,-1},{-1,0},{0,1}};

void _main() {
    cin >> R >> C;
    cin >> sy >> sx;
    cin >> gy >> gx;

    REP(i, R+1) REP(j, C+1) c[i][j] = '#';
    FOR(i, 1, R+1) FOR(j, 1, C+1) cin >> c[i][j];

    Pos S = {sy,sx};
    Pos G = {gy,gx};

    std::queue<Pos> q;
    q.push(S);

    map<Pos, int> steps;
    steps[S] = 0;

    while (true) {
        auto pos = q.front();
        q.pop();

        if (pos == G) break;

        for (auto p : nextPos) {
            Pos next = {pos.first + p.first, pos.second + p.second};
            if (c[next.first][next.second] == '#') continue;
            if (steps.count(next) != 0) continue;

            steps[next] = steps[pos] + 1;
            q.push(next);
        }
    }

    cout << steps[G] << endl;
}

int main() {
    _main();
    return 0;
}

// AC 30min

