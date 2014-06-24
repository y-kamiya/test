/*
 * K-th number (bucket)
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
typedef vector<int> V;

const int B = 1000;
const int N = 7, M = 3;
const int A[N] = {1,5,2,6,3,7,4};
const int I[M] = {2,4,1};
const int J[M] = {5,4,7};
const int K[M] = {3,1,3};

int nums[N];
vector<int> bucket[N/B];

void solve()
{
    for (int i = 0; i < N; i++) {
        bucket[i / B].push_back(A[i]);
        nums[i] = A[i];
    }
    sort(nums, nums + N);

    for (int i = 0; i < N / B; i++) {
        sort(bucket[i].begin(), bucket[i].end());
    }

    for (int i = 0; i < M; i++) {
        int l = I[i], r = J[i] + 1, k = K[i];

        int lb = -1, ub = N - 1;
        while (ub - lb > 1) {
            int md = (lb + ub) / 2;
            int x = nums[md];
            int tl = l, tr = r, c = 0;

            while (tl < tr && tl % B != 0) {
                if (A[tl++] <= x) c++;
            }
            while (tl < tr && tr % B != 0) {
                if (A[--tr] <= x) c++;
            }

            while (tl < tr) {
                int b = tl / B;
                c += upper_bound(bucket[b].begin(), bucket[b].end(), x) - bucket[b].begin();
                tl += B;
            }
            if (c >= k) ub = md;
            else lb = md;
        }

        printf("%d\n", nums[ub]);
    }

}

int main() 
{
    solve();
    return 0;
}
