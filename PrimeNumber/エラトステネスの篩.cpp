#include <bits/stdc++.h>
using namespace std;


vector<int> sieve(int n) {
    /***
     * エラトステネスの篩
     *
     * Descriptions:
     *  n以下の素数を格納したのvectorを返す
     *
     * Args:
     *  n(int): 正整数
     *
     * Return:
     *  primes: 素数を格納したvector
     *
     ***/
    vector<bool> is_prime(n+1, true);  // is_prime[i] := 整数iは素数かどうか
    is_prime[0] = false; is_prime[1] = false;

    vector<int> primes;  // 素数を格納する
    for (int i=2; i<n+1; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j=i*2; j<n+1; j+=i) {
                is_prime[j] = false;
            }
        }
    }
    return primes;
}


int main(int argc, char const *argv[]){
    vector<int> primes = sieve(100);
    for (int i=0; i<primes.size(); i++) {
        cout << primes[i] << endl;
    }
/*
2
3
5
7
11
13
17
19
23
29
31
37
41
43
47
53
59
61
67
71
73
79
83
89
97
*/
    return 0;
}
