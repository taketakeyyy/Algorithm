#include <bits/stdc++.h>
using namespace std;


/***
 * a^{n} mod m の計算を、繰り返し二乗法で求めるライブラリ
 ***/


long long mod_pow(long long a, long long n, long long m) {
    /** a^{n} mod m の計算を、繰り返し二乗法で求める
     *  計算量：O(log n)
     **/
    if (n==0) return 1;
    long long res = mod_pow(a*a%m, n/2, m);
    if (n&1) res = res * a % m;
    return res;
}


void test() {
    long long ans;
    long long a, n, m;

    a = 2LL; n = 20LL; m = pow(10, 9)+7;
    ans = mod_pow(a, n, m);
    cout << ans << endl;
    // 1048576

    a = 2LL; n = 1000000000LL; m = pow(10, 9)+7;
    ans = mod_pow(a, n, m);
    cout << ans << endl;
    // 140625001
}


int main(int argc, char const *argv[]){
    test();
    return 0;
}
