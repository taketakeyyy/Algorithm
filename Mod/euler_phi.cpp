#include <bits/stdc++.h>
using namespace std;

/**
 * オイラー関数Φ(n)を求める
 *
 * オイラー関数Φ(n)とは、「n以下の、nと互いに素な自然数の個数」を求める関数。
 * 「互いに素」=「gcdが1」
 *
 * オイラー関数の例
 *  Φ(10) = 4 (1,2,3,4,5,6,7,8,9,10のうち、10と互いに素なのは1,3,7,9の4つ)
 *
 * 計算量はO(√n)
 */
template<typename T>
T euler_phi(T n) {
    T res = n;
    for (T i=2; i*i<=n; i++) {
        if (n%i==0) {
            res = res / i * (i-1);
            for (; n%i==0; n/=i);
        }
    }
    if (n!=1) res = res / n * (n-1);
    return res;
}


/***
 * 1~nまでのオイラー関数の値のテーブルを作成する
 *
 * エラトステネスの篩の応用で、素因数が見つかるたびに(p-1)/pを掛けて更新することで
 * テーブルを作成することができる
 *
 * 計算量はO(n)程度
 ***/
template<typename T>
vector<T> euler_phi_table(T n) {
    vector<T> table(n+1);
    for (T i=0; i<=n; i++) table[i] = i;
    for (T i=2; i<=n; i++) {
        if (table[i]==i) {
            for (T j=i; j<=n; j+=i) table[j] = table[j] / i * (i-1);
        }
    }
    return table;
}


void test(){
    cout << euler_phi<long long>(10) << endl;
    // 4

    cout << "===euler_phi_table===" << endl;
    vector<long long> table;
    long long n = 10;
    table = euler_phi_table<long long>(n);
    for (int i=0; i<=n; i++) {
        cout << "table[" << i << "]:" << table[i] << endl;
    }

}


int main() {
    test();
    return 0;
}