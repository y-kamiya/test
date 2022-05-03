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
template<typename T, typename... Tail>
void print(vector<T> vec, Tail... t) {
    cout << "[";
    for (const auto &e : vec) {
        cout << e << ", ";
    }
    cout << "] ";
    print(t...);
}
#ifdef _DEBUG
#define DEBUG(...) print(__VA_ARGS__)
#else
#define DEBUG(...)
#endif

class SegmentTree {
    int n = 1;
    vector<int> node;

public:
    SegmentTree(vector<int> v) {
        int sz = v.size();
        while (n < sz) n <<= 1;
        node.resize(2*n-1, 0);

        REP(i, sz) node[i+n-1] = v[i];
        FORR(i, n-2, 0) node[i] = node[2*i+1] + node[2*i+2];
    }

    void add(int x, int val) {
        x += (n-1);
        node[x] += val;
        while (x > 0) {
            x = (x-1)/2;
            node[x] = node[2*x+1] + node[2*x+2];
        }
    }

    int getsum(int a, int b, int k=0, int l=0, int r=-1) {
        if (r < 0) r = n;
        if (b <= l || r <= a) return 0;
        if (a <= l && r <= b) return node[k];

        int mid = (l+r)/2;
        auto vl = getsum(a, b, 2*k+1, l, mid);
        auto vr = getsum(a, b, 2*k+2, mid, r);
        return vl + vr;
    }
};

void _main() {
    int n, q;
    cin >> n >> q;

    SegmentTree seg(vector<int>(n, 0));

    REP(i, q) {
        int c, x, y;
        cin >> c >> x >> y;
        if (c == 0) seg.add(x-1, y);
        if (c == 1) cout << seg.getsum(x-1, y) << endl;
    }


}

int main() {
    _main();
    return 0;
}

