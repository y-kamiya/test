/*
 * エラトステネスの篩
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>

#define N 100
using namespace std;

bool is_prime[N+1];
int prime[N];

int sieve(int n) 
{
    int p = 0;
    fill(is_prime, is_prime + N + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            prime[p++] = i;
            for (int j = 2 * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return p;
}

int main() 
{
    cout << "number of primes under 10: " << sieve(10) << endl;
    return 0;
}

