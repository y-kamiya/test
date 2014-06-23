/*
 * prime
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>

using namespace std;


int is_prime(int n) 
{
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return n != 1;
}

vector<int> divisor(int n) 
{
    vector<int> res;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            res.push_back(i);
            if (i != n / i) res.push_back(n / i);
        }
    }
    return res;
}

map<int,int> prime_factor(int n) 
{
    map<int, int> res;
    for (int i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            ++res[i];
            n /= i;
        }
    }
    if (n != 1) res[n] = 1;
    return res;
}

int main() 
{
    cout << "Is 13 prime ?  " << is_prime(13) << endl;

    vector<int> res = divisor(16);
    cout << "16 : ";
    for (vector<int>::iterator it = res.begin(); it != res.end(); it++) {
        cout << *it << ", ";
    }
    cout << endl;

    map<int, int> primes = prime_factor(16);
    cout << "16 : ";
    for (map<int, int>::iterator it = primes.begin(); it != primes.end(); it++) {
        cout << (*it).first << ": " << (*it).second << ", ";
    }
    cout << endl;
    return 0;
}

