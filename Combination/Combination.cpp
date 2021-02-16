#include <bits/stdc++.h>
using namespace std;

template<typename T>
T combination(T n, T r) {
    /***nCrは、O(min(n-r, r))で実装する

    Example:
        100C98 = 100!/(98!*2!)
               = 100*99/2*1
        となることから、計算量は減らせる

    Notes:
        分子と分母がかなり大きな値になった場合、計算は遅くなるので注意
        求める値がmodをとった値でいい場合、後述のフェルマーの小定理を使った方法が速い。
    ***/
    if (n < r) return 0;

    r = min(n-r, r);
    T bunsi=1, bunbo=1;
    for (T i=0; i<r; i++) {
        bunsi = bunsi*(n-i);
        bunbo = bunbo*(i+1);
    }
    return bunsi/bunbo;
}

template<typename T>
T mod_pow(T a, T n, T m) {
    /** a^{n} mod m の計算を、繰り返し二乗法で求める
     *  計算量：O(log n)
     **/
    if (n==0) return 1;
    T res = mod_pow(a*a%m, n/2, m);
    if (n&1) res = res * a % m;
    return res;
}

template <typename T>
T combination_mod(T n, T r, T mod) {
    /*** nCrを O(min(n-r, r)) で高速に計算する ***/
    auto inv = [mod](T x) { return mod_pow<T>(x, mod-2, mod); };

    r = min(n-r, r);
    T bunsi=1, bunbo=1;
    for (T i=0; i<r; i++) {
        bunsi = bunsi*(n-i)%mod;
        bunbo = bunbo*(i+1)%mod;
    }
    return (bunsi*inv(bunbo))%mod;
}

void test(){
    cout << "===test===" << endl;
    long long mod = pow(10, 9)+7;
    long long n=100, r=98;
    long long ans1 = combination(n, r);
    long long ans2 = combination_mod(n, r, mod);
    cout << ans1 << endl;
    // 4950
    cout << ans2 << endl;
    // 4950
}

void test2(){
    cout << "===test2===" << endl;
    long long mod = pow(10, 9)+7;
    long long n=pow(10,6), r=1000;
    // long long ans1 = combination(n, r);
    // cout << ans1 << endl;  // 10 [main] a 368 cygwin_exception::open_stackdumpfile: Dumping stack trace to a.exe.stackdump
    long long ans2 = combination_mod(n, r, mod);
    cout << ans2 << endl;
    // 735067492
}

int main(int argc, char const *argv[]){
    test();
    test2();
    return 0;
}