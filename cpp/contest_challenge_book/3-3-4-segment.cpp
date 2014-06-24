/*
 * K-th number (segment tree)
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>
#include <set>

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

#define INF 1000000

using namespace std;

typedef long long ll;

const int ST_SIZE = (1 << 18) - 1;
const int N = 7, M = 3;
const int A[N] = {1,5,2,6,3,7,4};
const int I[M] = {2,4,1};
const int J[M] = {5,4,7};
const int K[M] = {3,1,3};

int nums[N];
vector<int> dat[ST_SIZE];

void init(int k, int l, int r)
{
    if (r - l == 1) {
        dat[k].push_back(A[l]);
    } else {
        int lch = k * 2 + 1, rch = k * 2 + 2;
        init(lch, l, (l + r) / 2);
        init(rch, (l + r) / 2, r);
        dat[k].resize(r - 1);

        merge(dat[lch].begin(), dat[lch].end(), dat[rch].begin(), dat[rch].end(), dat[k].begin());
    }
}

int query(int i, int j, int x, int k, int l, int r)
{
    if (j <= l || r <= i) {
        return 0;
    } else if (i <= l && r <= i) {
        return upper_bound(dat[k].begin(), dat[k].end(), x) - dat[k].begin();
    } else {
        int lc = query(i, j, x, k * 2 + 1, l, (l + r) / 2);
        int rc = query(i, j, x, k * 2 + 2, (l + r) / 2, r);
        return lc + rc;
    }
}

int main() 
{
    for (int i = 0; i < N; i++) {
        nums[i] = A[i];
    }
    sort(nums, nums + N);

    init(0,0,N);

    for (int i = 0; i < M; i++) {
        int l = I[i], r = J[i], k = K[i];
        int lb = -1, ub = N - 1;
        while (ub - lb > 1) {
            int md = (ub + lb) / 2;
            int c = query(l, r, nums[md], 0, 0, N);
            if (c >= k) ub = md;
            else lb = md;
        }
        printf("%d\n", nums[ub]);
    }
    return 0;
}
