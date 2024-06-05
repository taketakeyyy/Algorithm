#include <bits/stdc++.h>
using namespace std;


/**
 * @brief パスカルの三角形で二項定理nCrを求める
 * 計算量O(N^2)
 *
 * @param N N行目までの二項定理NCrを求める
 * @return vector<vector<ll>> 二項定理C[n][r] := nCr
 *
 * @note
 * 二項定理を足し算で求めていくので、オーバーフローに少し強い。
 * long long型で、
 *  - C[200][12]はオーバーフローしない。
 *  - C[200][13]はオーバーフローする。
 * なので、用途は限定的。
 *
 * @example
 * // N=200までの二項定理を作成
 * vector<vector<ll>> combo = combination_pascal_triangle<ll>(200);
 * cout << combo[6][2] << endl; // 15
 */
template<typename T>
vector<vector<T>> combination_pascal_triangle(T N) {
    vector<vector<T>> C(N+1);
    for(T n=0; n<N+1; n++) {
        C[n].assign(n+1, 1);
    }
    // パスカルの三角形で二項定理を求めていく
    for(T n=2; n<N+1; n++) {
        for(T r=1; r<=n-1; r++) {
            C[n][r] = C[n-1][r-1] + C[n-1][r];
        }
    }
    return C;
}
vector<vector<long long>> combo = combination_pascal_triangle<long long>(200);

void test1(){
    cout << "===test1===" << endl;
    cout << combo[6][2] << endl; // 15
}

void test2(){
    cout << "===test2===" << endl;
    cout << combo[200][12] << endl; // 6107693672247476400
}

int main(){
    test1();
    test2();
    return 0;
}