#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define MOD 1000000007


/** 自動でMODをとるModInt型
 *
 * Usage
 *   // 基本的な使い方
 *   mint a, b;
 *   a = 100;
 *   b = a + MOD;
 *   // istreamとostreamをオーバロードしてるので、mint型も普通に入出力できる
 *   cout << b << endl;  // 100
 *   // 明示的にlong long型を出力するときは.xを参照する
 *   cout << b.x << endl;  // 100
 *
 * References
 *  https://youtu.be/L8grWxBlIZ4?t=9858
 *  https://youtu.be/ERZuLAxZffQ?t=4807 : optimize
 *  https://youtu.be/8uowVvQ_-Mo?t=1329 : division
 */
struct mint {
    ll x; // typedef long long ll;
    mint(ll x=0):x((x%MOD+MOD)%MOD){}
    mint operator-() const { return mint(-x);}
    mint& operator+=(const mint a) {
        if ((x += a.x) >= MOD) x -= MOD;
        return *this;
    }
    mint& operator-=(const mint a) {
        if ((x += MOD-a.x) >= MOD) x -= MOD;
        return *this;
    }
    mint& operator*=(const mint a) { (x *= a.x) %= MOD; return *this;}
    mint operator+(const mint a) const { return mint(*this) += a;}
    mint operator-(const mint a) const { return mint(*this) -= a;}
    mint operator*(const mint a) const { return mint(*this) *= a;}
    mint pow(ll t) const {
        if (!t) return 1;
        mint a = pow(t>>1);
        a *= a;
        if (t&1) a *= *this;
        return a;
    }

    // for prime MOD
    mint inv() const { return pow(MOD-2);}
    mint& operator/=(const mint a) { return *this *= a.inv();}
    mint operator/(const mint a) const { return mint(*this) /= a;}
};
istream& operator>>(istream& is, mint& a) { return is >> a.x;}
ostream& operator<<(ostream& os, const mint& a) { return os << a.x;}


/**
 * @brief mintを使った高速なnPr計算
 *
 * @tparam T
 *
 * @details
 *  O(n)で前計算を構築し、nPrのクエリにO(1)で応答する
 *
 *  * 0!, 1!, ..., (n-1)!, n!
 *  * 1/n!, 1/(n-1)!, ..., 1/0!
 *  のテーブルをそれぞれO(n)で構築する。
 *
 *  それにより nPr = n!/(n-r)! のクエリにO(1)で応答できる
 *
 * @usage
 *  permutation_mint_builder<ll> p(1e6);
 *  mint ans = p(6,2);  // 6P2
 */
template <typename T>
struct permutation_mint_builder {
    vector<mint> fact, ifact;
    permutation_mint_builder(T n) {
        assert(n < MOD);
        fact.resize(n+1); ifact.resize(n+1);
        fact[0] = 1;
        for(T i=1; i<=n; i++) fact[i] = fact[i-1]*i;
        ifact[n] = fact[n].inv();
        for(T i=n; i>=1; i--) ifact[i-1] = ifact[i]*i;
    }
    mint operator()(T n, T r) {
        if (r<0 || r>n) return 0;
        return fact[n]*ifact[n-r];
    }
};


void test1(){
    cout << "===test1===" << endl;
    permutation_mint_builder<ll> p(1e6);
    ll n=20, r=5;
    mint ans = p(n, r);
    cout << ans << endl;
    // 1860480
}

void test2(){
    cout << "===test2===" << endl;
    permutation_mint_builder<ll> p(1e6);
    ll n=1e6, r=1e5;
    mint ans = p(n, r);
    cout << ans << endl;
    // 431436174
}


int main(){
    test1();
    test2();
    return 0;
}