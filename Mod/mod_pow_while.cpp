#include <bits/stdc++.h>
using namespace std;


/**
 * @brief a^{n} mod m の計算を、繰り返し二乗法で求める
 * 計算量：O(log n)
 **/
template<typename T>
T mod_pow(T a, T n, T m) {
    T res = 1;
    while(n > 0) {
        if (n&1) res = (res*a)%m;
        n >>= 1;
        a = (a*a)%m;
    }
    return res;
}

void test1() {
    cout << "===test1===" << endl;
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


int main(){
    test1();
    return 0;
}
