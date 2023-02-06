#include <bits/stdc++.h>
using namespace std;

/**
 * @brief 二項係数nCrを計算する
 * @details
 * nCrは、O(min(n-r, r))で実装する
 *         100C98 = 100!/(98!*2!)
 *                = 100*99/2*1
 * @note
 * かなりナイーブな実装なので、すぐオーバーフローすることに注意。
 * long long で n=66 までならオーバーフローしない combination_rec を検討すること。
 * 求める値がmodを取った値でいい場合、combination_modを使うとこと。
 */
template<typename T>
T combination_naive(T n, T r) {
    if (n < r) return 0;

    r = min(n-r, r);
    T bunsi=1, bunbo=1;
    for (T i=0; i<r; i++) {
        bunsi = bunsi*(n-i);
        bunbo = bunbo*(i+1);
    }
    return bunsi/bunbo;
}

/**
 * @brief a^{n} mod m の計算を、繰り返し二乗法で求める
 * 計算量：O(log n)
 **/
template<typename T>
T mod_pow(T a, T n, T m) {
    if (n==0) return 1;
    T res = mod_pow(a*a%m, n/2, m);
    if (n&1) res = res * a % m;
    return res;
}

/**
 * @brief nCrをmodで割った値を求める
 * フェルマーの小定理 + 繰り返し二乗法で高速に計算する
 */
template <typename T>
T combination_mod(T n, T r, T mod) {
    auto inv = [mod](T x) { return mod_pow<T>(x, mod-2, mod); };

    r = min(n-r, r);
    T bunsi=1, bunbo=1;
    for (T i=0; i<r; i++) {
        bunsi = bunsi*(n-i)%mod;
        bunbo = bunbo*(i+1)%mod;
    }
    return (bunsi*inv(bunbo))%mod;
}

/**
 * @brief 二項係数C(n,r)
 * @details
 * nCr = n-1Cr-1 + n-1Cr でメモ化再帰で求める
 * n=66 までならlong longでオーバーフローしないことが保証される
 *   - C(66,33) ≒ 7e18 （long long だとギリギリ収まる）
 */
template<typename T>
T combination_rec(T n, T r) {
    static vector c_memo(67, vector<T>(67, -1)); // 二項係数のメモ

    r = min(n-r, r);
    if (r < 0) return 0;
    if (c_memo[n][r] != -1) return c_memo[n][r];
    if (n == 0) return c_memo[n][r] = 1;
    if (r == 0) return c_memo[n][r] = 1;
    return c_memo[n][r] = combination_rec<T>(n-1, r-1) + combination_rec<T>(n-1, r);
}


void test1(){
    cout << "===test1===" << endl;
    long long mod = pow(10, 9)+7;
    long long n=100, r=98;
    long long ans1 = combination_naive(n, r);
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

void test3(){
    cout << "===test3===" << endl;
    cout << combination_naive<long long>(66, 33) << endl;
    // -1 (オーバーフローして正しく計算できていない)
    cout << combination_rec<long long>(66, 33) << endl;
    // 7219428434016265740
}

int main(){
    test1();
    test2();
    test3();
    return 0;
}