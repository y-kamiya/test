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


static const int MAX = 1005;
int H, W, N;
char MAP[MAX][MAX];

using Pos = pair<int,int>;
Pos NEXT[4] = {{0,1}, {1,0}, {0,-1}, {-1,0}};

int bfs(Pos s, Pos g) {
    map<Pos, int> time;
    time[s] = 0;

    queue<Pos> q;
    q.push(s);

    while (true) {
        if (q.size() == 0) break;

        Pos pos = q.front();
        q.pop();

        // cout << "aaaaaaaaaaaaaaaaa: " << g.second << ", " << g.first << "  " << q.size() << endl;
        if (pos == g) break;

        // cout << "bbbbbbbbb: " << pos.second << ", " << pos.first << "  " << q.size() << endl;
        for (auto p : NEXT) {
            Pos next = {pos.first + p.first, pos.second + p.second};
            if (MAP[next.first][next.second] == 'X' || next.first < 0 || next.second < 0) continue;
            if (time.count(next) != 0) continue;

            // cout << "ccccccccccccc: " << next.second << ", " << next.first << endl;
            q.push(next);
            time[next] = time[pos] + 1;
        }
    }

    return time[g];
}

void _main() {
    cin >> H >> W >> N;
    REP(i, MAX) REP(j, MAX) MAP[i][j] = 'X';

    Pos START[N+1];
    REP(i, H) REP(j, W) {
        char c;
        cin >> c;
        if (c == 'X' || c == '.') MAP[i][j] = c;
        else {
            MAP[i][j] = '.';
            if (c == 'S') START[0] = {i,j};
            else START[c-'0'] = {i,j};
        }
    }

    int time = 0;
    REP(i, N){
        time += bfs(START[i], START[i+1]);
    }

    cout << time << endl;
}

int main() {
    _main();
    return 0;
}

