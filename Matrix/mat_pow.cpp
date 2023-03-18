#include <bits/stdc++.h>
using namespace std;

/**
 * @brief 行列Aと行列Bのドット内積を計算する
 * 行列計算 AB を計算する
 *
 * @tparam T
 * @param A 行列
 * @param B 行列
 * @param mod
 * @return vector<vector<T>>
 */
template<typename T>
vector<vector<T>> mat_mul(vector<vector<T>> const &A, vector<vector<T>> const &B, T mod) {
    T rowA = A.size(); // 行数
    T colA = A[0].size(); // 列数
    T rowB = B.size(); // 行数
    T colB = B[0].size(); // 列数
    if (colA != rowB) throw runtime_error("cannot mat_mul.");

    vector<vector<T>> res(rowA, vector<T>(colB));
    for(size_t i=0; i<(size_t)rowA; i++) {
        for(size_t j=0; j<(size_t)colB; j++) {
            for(size_t k=0; k<(size_t)colA; k++) {
                res[i][j] += A[i][k]*B[k][j];
                res[i][j] %= mod;
            }
        }
    }
    return res;
}

/**
 * @brief 行列累乗
 * 行列Aをn乗する。
 *
 * @tparam T
 * @param A 行列
 * @param n n乗する
 * @param mod
 * @return vector<vector<T>>
 */
template <typename T>
vector<vector<T>> mat_pow(vector<vector<T>> A, T n, T mod) {
    size_t row = A.size();
    size_t col = A[0].size();
    if (row != col) throw runtime_error("cannot mat_pow.");

    vector<vector<T>> res(row, vector<T>(col));
    for(size_t i=0; i<row; i++) res[i][i] = 1; // 単位行列

    while(n > 0) {
        if (n&1) res = mat_mul(res, A, mod);
        A = mat_mul(A, A, mod);
        n >>= 1;
    }
    return res;
}

// フィボナッチ数列を行列累乗で計算する。
// F(1) = 1
// F(2) = 1
// F(n) = F(n-1) + F(n-2)
// フィボナッチ数計算サイト：https://keisan.casio.jp/exec/system/1161228773
void test1() {
    cout << "===test1===" << endl;
    const long long mod = LONG_LONG_MAX;
    // F(80)を求める
    vector<vector<long long>> mat = {{1,1},{1,0}};
    auto res = mat_pow<long long>(mat, 78, mod);
    vector<vector<long long>> ini = {{1},{1}};
    auto ans = mat_mul<long long>(res, ini, mod);
    cout << ans[0][0] << endl;
    // 23,416,728,348,467,685
}

// ABC293 E - Geometric Progression
// https://atcoder.jp/contests/abc293/tasks/abc293_e
// 入力例1
// 3 4 7
void test2() {
    cout << "===test2===" << endl;
    long long A=3, X=4, M=7;
    vector mat(2, vector<long long>(2));
    mat[0][0] = A; mat[0][1] = 1;
    mat[1][0] = 0; mat[1][1] = 1;
    auto mat2 = mat_pow(mat, X, M);
    cout << mat2[0][1] << endl;
    // 5
}


int main() {
    test1();
    test2();
    return 0;
}