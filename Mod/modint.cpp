#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int,int>;


/* 自動でMODをとるModInt
https://youtu.be/L8grWxBlIZ4?t=9858
https://youtu.be/ERZuLAxZffQ?t=4807 : optimize
https://youtu.be/8uowVvQ_-Mo?t=1329 : division
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


void test(void) {
    /* 基本的な使い方 */
    mint a, b;
    a = 100;
    b = a + MOD;
    /* istreamとostreamをオーバロードしてるので、mint型も普通に入出力できる */
    cout << b << endl;  // 100
    /* 明示的にlong long型を出力するときは.xを参照する */
    cout << b.x << endl;  // 100

    /* 二次元配列 dp[H][W] の作成 */
    int H=100, W=200;
    vector<vector<mint>> dp(H, vector<mint>(W, 0));

    /* 逆元を計算する */
    // modintの「3で割る」は、「3の逆元をかける」に等しい
    // inv()の計算は重いので、予め計算しておく
    mint inv3 = mint(3).inv();
    cout << inv3 << endl;  // 333333336

    /* 割り算の注意 */
    // 普通に割り算してOKだが、割り算の内部処理のinv()の計算は重いので注意
    mint c = 100;
    c /= 3;
    cout << c << endl;  // 333333369

    // なので、何回も3で割るなら、あらかじめ3の逆元を計算しておき、「3の逆元をかける」方が高速
    c = 100;
    c *= inv3;
    cout << c << endl;  // 333333369
}

int main(int argc, char const *argv[]){
    test();
    return 0;
}