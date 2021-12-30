#include <bits/stdc++.h>
using namespace std;


/***
 * a^{n} mod m の計算を、繰り返し二乗法で求めるライブラリ
 ***/

template<typename T>
T mod_pow(T a, T n, T m) {
    /** a^{n} mod m の計算を、繰り返し二乗法で求める
     *  計算量：O(log n)
     **/
    if (n==0) return 1;
    a %= m;
    T res = mod_pow(a*a, n/2, m);
    if (n&1) res = (res * a) % m;
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
