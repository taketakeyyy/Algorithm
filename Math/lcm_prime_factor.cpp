#include <bits/stdc++.h>
using namespace std;

/*
正整数nを素因数分解して、因数をkey、指数部をvalueとしたmapを返す関数
*/
template <typename T>
map<T, T> prime_factor_ver_map(T n) {
    map<T, T> ans;
    if (n <= 1) return ans;

    for (T i=2; i*i<=n; i++) {
        while (n%i == 0) {
            ans[i]++;
            n /= i;
        }
    }

    if (n != 1) ans[n]++;

    return ans;
}

template <typename T>
void lcm_prime_factor(map<T,T> &mpa, map<T,T> mpb) {
    /* 最小公倍数lcm(a,b)の結果を、素因数分解で保持する
     * Args:
     *   mpa: aの素因数分解
     *   mpb: bの素因数分解
     */
    for(auto [p, q]: mpb) {
        mpa[p] = max(mpa[p], mpb[p]);
    }
}


void test() {
    // 確認用サイト:https://keisan.casio.jp/exec/system/1161228772
    cout << "===test===" << endl;
    int a = 630;
    int b = 300;
    map<int,int> mpa = prime_factor_ver_map<int>(a);
    map<int,int> mpb = prime_factor_ver_map<int>(b);
    lcm_prime_factor(mpa, mpb);

    // 出力
    int ans = 1;
    for(auto [p,q]:mpa) {
        for(int i=0; i<q; i++) ans *= p;
    }
    cout << ans << endl;
    // 6300
}

void test2() {
    // 確認用サイト:https://keisan.casio.jp/exec/system/1161228772
    cout << "===test2===" << endl;
    int a = 1234;
    int b = 6789;
    map<int,int> mpa = prime_factor_ver_map<int>(a);
    map<int,int> mpb = prime_factor_ver_map<int>(b);
    lcm_prime_factor(mpa, mpb);

    // 出力
    int ans = 1;
    for(auto [p,q]:mpa) {
        for(int i=0; i<q; i++) ans *= p;
    }
    cout << ans << endl;
    // 8377626
}

int main() {
    test();
    test2();
    return 0;
}