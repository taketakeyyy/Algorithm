#include <bits/stdc++.h>
using namespace std;

template<typename T>
vector<T> segment_sieve(T a, T b) {
    /***
     * 区間 [a,b) に対してエラトステネスの篩をする
     *
     * Args
     *  a(int): 正整数
     *  b(int): 正整数
     *
     * Return
     *  primes(vector<int>): 区間 [a,b) の素数のリスト
     *
     ***/
    vector<bool> is_prime_small(ceil(pow(b,0.5)), true);
    vector<bool> is_prime(b-a, true);  // is_prime[i-a] = true <=> iが素数

    for(T i=2LL; i*i<b; i++) {
        if (is_prime_small[i]) {
            // [2,√b)の篩
            for (T j=i*2LL; j*j<b; j+=i) {
                is_prime_small[j] = false;
            }
            // [a,b)の篩
            for (T j=max(2LL,(a+i-1LL)/i)*i; j<b; j+=i) {
                is_prime[j-a] = false;
            }
        }
    }

    vector<T> primes;
    for (T i=0; i<is_prime.size(); i++) {
        if (is_prime[i]) {
            primes.push_back(a+i);
        }
    }
    return primes;
}

void test1() {
    cout << "=== test1 ===" << endl;
    long long a, b;
    vector<long long> primes;

    a=6LL; b=18LL;
    primes = segment_sieve<long long>(a, b);
    for (long long i=0LL; i<primes.size(); i++) {
        cout << primes[i] << endl;
    }
/*
7
11
13
17
*/
}

void test2() {
    cout << "=== test2 ===" << endl;
    long long a, b;
    vector<long long> primes;

    a=22LL; b=37LL;
    primes = segment_sieve<long long>(a, b);
    for (long long i=0; i<primes.size(); i++) {
        cout << primes[i] << endl;
    }
/*
23
29
31
*/
}

void test3() {
    cout << "=== test3 ===" << endl;
    long long a, b;
    vector<long long> primes;

    a=22801763489; b=22801787297;
    primes = segment_sieve<long long>(a, b);
    for (long long i=0; i<primes.size(); i++) {
        cout << primes[i] << endl;
    }
/*
22801763489
22801763513
22801763527
22801763531
...
22801787291
*/
}

int main() {
    test1();
    test2();
    test3();

    return 0;
}