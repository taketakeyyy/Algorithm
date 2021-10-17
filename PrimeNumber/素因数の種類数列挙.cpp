#include <bits/stdc++.h>
using namespace std;

/***素因数の種類数列挙
 * 1以上N以下の各整数の素因数の種類数を計算する
 *
 * Args:
 *  N(T): 1以上N以下の整数
 * Notes:
 *  計算量はO(NloglogN)
 **/
template <typename T>
vector<T> prime_factor_number_of_types(T N) {
    vector<T> C(N+1, 0);
    for(T i=2; i<=N; i++) {
        if (C[i] != 0) continue;  // これで素数判定をしている
        for(T j=i; j<=N; j+=i) C[j]++;
    }
    return C;
}


void test1(){
    // 030 - K Factors（★5）の入力例を試す
    // https://atcoder.jp/contests/typical90/tasks/typical90_ad
    long long N = 15;
    vector<long long> enums = prime_factor_number_of_types<long long>(N);

    for(long long i=2; i<=N; i++) {
        cout << i << ": " << enums[i] << endl;
    }
    // 2: 1
    // 3: 1
    // 4: 1
    // 5: 1
    // 6: 2 (2と3)
    // 7: 1
    // 8: 1
    // 9: 1
    // 10: 2 (2と5)
    // 11: 1
    // 12: 2 (2と3)
    // 13: 1
    // 14: 2 (2と7)
    // 15: 2 (3と5)
}


int main(int argc, char const *argv[]){
    test1();
    return 0;
}