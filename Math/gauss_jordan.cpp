#include <bits/stdc++.h>
using namespace std;
// using ll = long long;
// using vec = vector<double>;
// using mat = vector<vec>;

/***
 * Gauss-Jordanの消去法
 *  計算量はO(n^3) （nは式の数）
 ***/
template<typename T>
vector<T> gauss_jordan(const vector<vector<T>>& A, const vector<T>& b) {
    /***
     * Ax=bを解く
     * Aは正方行列
     *   - つまり、式の数と変数の数は同数にすること
     * 解が存在しないか、一意でない場合は長さ0の配列を返す
     **/
    const double EPS = 1E-8;
    size_t n = A.size();
    vector<vector<T>> B(n, vector<T>(n+1));
    for (size_t i=0; i<n; i++) {
        for (size_t a=0; a<n; a++) {
            B[i][a] = A[i][a];
        }
    }
    // 行列Aの後ろにbを並べて同時に処理する
    for (size_t i=0; i<n; i++) {
        B[i][n] = b[i];
    }

    for (size_t a=0; a<n; a++) {
        // 注目している変数の係数の絶対値が大きい式をa番目に持ってくる
        size_t pivot = a;
        for (size_t j=a; j<n; j++) {
            if (abs(B[j][a]) > abs(B[pivot][a])) {
                pivot = j;
            }
        }
        swap<double>(B[a], B[pivot]);

        // 解がないか、一意でない
        if (abs(B[a][a]) < EPS) return vector<T>();

        // 注目している変数の係数を1にする
        for (size_t j=a+1; j<=n; j++) B[a][j] /= B[a][a];
        for (size_t j=0; j<n; j++) {
            if (a==j) continue;
            // j番目の式からa番目の変数を消去する
            for (size_t k=a+1; k<=n; k++) {
                B[j][k] -= B[j][a] * B[a][k];
            }
        }
    }
    vector<double> x(n);
    // 後ろに並べたbが解になる
    for (size_t i=0; i<n; i++) x[i] = B[i][n];
    return x;
}

void test(){
    cout << "===test===" << endl;
    //  x - 2y + 3z  = 6
    // 4x - 5y + 6z  = 12
    // 7x - 8y + 10z = 21
    // を解くと、
    // x=1, y=2, z=3である。
    // これをGauss-Jordanの消去法を使って解く

    // Ax=bを解きたいので、Aとbを作成する
    int n = 3;
    vector<vector<double>> A(n, vector<double>(n));  // Aは正方行列
    A[0][0]=1; A[0][1]=-2; A[0][2]=3;
    A[1][0]=4; A[1][1]=-5; A[1][2]=6;
    A[2][0]=7; A[2][1]=-8; A[2][2]=10;

    vector<double> b(n);
    b[0]=6; b[1]=12; b[2]=21;

    vector<double> ans;
    ans = gauss_jordan<double>(A, b);

    // 出力
    if (ans.size()==0) {
        cout << "解なし or 一意でない" << endl;
        return;
    }
    for (int i=0; i<n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
    // 1 2 3
}


int main(int argc, char const *argv[]){
    test();
    return 0;
}