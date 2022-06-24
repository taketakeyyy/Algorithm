#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/***
 * 包除原理のライブラリ
 ***/
template<typename T>
T inclusion_exclusion_principle(T n, vector<T> A) {
    /*** 包除原理
     * 1以上n以下の整数で、配列Aのうち少なくとも1つで割り切れるものの個数を返す
     *
     * 計算量は、配列Aの大きさをmとし、|Ai ∩ Aj ∩ ... ∩ Ak| を1つ計算するのにかかる時間をO(f)とすると、
     * 全体ではO(2^m f)
     ***/
    T res = 0;
    T m = A.size();
    for (T i=1; i<(1<<m); i++) {
        T num = 0;
        for (T j=i; j!=0; j>>=1) {
            num += j&1;  // iの立っているビットの個数
        }
        T lcm = 1;
        for (T j=0; j<m; j++) {
            if (i>>j&1) {
                lcm = lcm / gcd(lcm, A[j]) * A[j];
                // lcmがnを超えるとn/lcm=0なので、オーバーフローする前にbreakする
                if (lcm > n) break;
            }
        }
        if (num%2==0) {
            res -= n/lcm;
        }
        else {
            res += n/lcm;
        }
    }
    return res;
}


void test() {
    cout << "===test===" << endl;
    ll n = 100;
    vector<ll> A = {2,3};
    ll ans = inclusion_exclusion_principle<ll>(n, A);
    cout << ans << endl;
    // 67 (2の倍数が50個、3の倍数が33個、6の倍数が16個なので、50+33-16=67個)
}

void test2() {
    cout << "===test2===" << endl;
    ll n = 100;
    vector<ll> A = {2,3,7};
    ll ans = inclusion_exclusion_principle<ll>(n, A);
    cout << ans << endl;
    // 72
}


int main(int argc, char const *argv[]){
    test();
    test2();
    return 0;
}