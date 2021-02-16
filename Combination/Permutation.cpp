#include <bits/stdc++.h>
using namespace std;

// # n個の中からr個を取り出す順列の組み合わせ数は
// # nPr = n!/(n-r)!
// # 階乗部分を展開して割り算すれば、Π(n-r+1, n)なので、計算量はO(r-1)
template<typename T>
T permutation(T n, T r) {
    T ans = 1;
    for (T i=n; i>n-r; --i) {
        ans = ans*i;
    }
    return ans;
}

// # 求める値がmodをとった値の場合は以下のようになる。計算量は変わらない。
template<typename T>
T permutation_mod(T n, T r, T mod) {
    T ans = 1;
    for (T i=n; i>n-r; --i) {
        ans = (ans*i)%mod;
    }
    return ans;
}

void test(){
    cout << "===test===" << endl;
    long long mod = pow(10,9)+7;
    long long n=20, r=5;
    long long ans1 = permutation(n, r);
    long long ans2 = permutation_mod(n, r, mod);
    cout << ans1 << endl;
    // 1860480
    cout << ans2 << endl;
    // 1860480
}

void test2() {
    cout << "===test2===" << endl;
    long long mod = pow(10,9)+7;
    long long n=pow(10,6), r=pow(10,5);
    long long ans1 = permutation(n, r);
    long long ans2 = permutation_mod(n, r, mod);
    cout << ans1 << endl;
    // 0
    cout << ans2 << endl;
    // 431436174
}


int main(int argc, char const *argv[]){
    test();
    test2();
    return 0;
}