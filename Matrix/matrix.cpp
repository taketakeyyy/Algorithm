#include <bits/stdc++.h>
using namespace std;


namespace MatrixLib {
    class print_format_error: public std::exception {
        virtual const char* what() const noexcept { return "Error: print() method cannot print these values because of unsupported!"; }
    };
    class matrix_product_error: public std::exception {
        virtual const char* what() const noexcept { return "Error: Impossible to calculate matrix product!"; }
    };
    class determinant_error: public std::exception {
        virtual const char* what() const noexcept { return "Error: Impossible to calculate determinant!"; }
    };
    class inversion_error: public std::exception {
        virtual const char* what() const noexcept { return "Error: Impossible to calculate inversion!"; }
    };


    /*** 二次元行列のライブラリMatrix ***/
    template <typename T>
    class Matrix {
        private:
            vector<vector<T>> A;

            T __cofactor(const vector<vector<T>>& coA) const {
                /* 各余因子の計算を再帰的にする */
                if (coA.size() == 1) return coA[0][0];
                if (coA.size() == 2) {
                    return coA[0][0]*coA[1][1]-coA[0][1]*coA[1][0];
                }

                T res = 0;
                for (int col2=0; col2<coA.size(); col2++) {
                    vector<vector<T>> cocoA(coA.size()-1);
                    for (int row=1; row<coA.size(); row++) {
                        for (int col=0; col<coA.size(); col++) {
                            if (col2==col) continue;
                            cocoA[row-1].emplace_back(coA[row][col]);
                        }
                    }
                    if (!(col2&1)) res += coA[0][col2] * __cofactor(cocoA);
                    else res -= coA[0][col2] * __cofactor(cocoA);
                }
                return res;
            }
        public:
            size_t row;
            size_t col;
            Matrix(size_t row=1, size_t col=1) {
                this->row = row;
                this->col = col;
                this->A.resize(row);
                for(size_t i=0; i<row; i++) this->A[i].resize(col);
            }

            vector<T>& operator[](const size_t i) {
                return this->A[i];
            }

            Matrix& operator+=(Matrix other) {
                for(size_t i=0; i<this->row; i++) {
                    for(size_t j=0; j<this->col; j++) {
                        this->A[i][j] += other[i][j];
                    }
                }
                return *this;
            }
            Matrix operator+(const Matrix other) const {
                return Matrix(*this) += other;
            }

            Matrix& operator-=(Matrix other) {
                for(size_t i=0; i<this->row; i++) {
                    for(size_t j=0; j<this->col; j++) {
                        this->A[i][j] -= other[i][j];
                    }
                }
                return *this;
            }
            Matrix operator-(const Matrix other) const {
                return Matrix(*this) -= other;
            }
            Matrix operator-() const {
                Matrix res(this->row, this->col);
                for (size_t i=0; i<this->row; i++) {
                    for (size_t j=0; j<this->col; j++) {
                        res[i][j] = -this->A[i][j];
                    }
                }
                return res;
            }

            Matrix& operator*=(Matrix other) {
                /* NxN行列 x NxN行列 の積を求める */
                if (!(this->row==this->col && other.row==other.col && this->row==other.row)) throw matrix_product_error();

                vector<vector<T>> res(this->row, vector<T>(this->col, 0));
                for(size_t i=0; i<other.row; i++) {
                    for (size_t j=0; j<this->col; j++) {
                        for (size_t k=0; k<this->col; k++) {
                            res[i][j] += this->A[i][k]*other[k][j];
                        }
                    }
                }
                this->A = res;
                return *this;
            }
            Matrix operator*(Matrix other) const {
                /* ixk行列 * kxj行列 の積を求める */
                if (this->col!=other.row) throw matrix_product_error();

                Matrix<T> res(this->row, other.col);
                for (size_t i=0; i<this->row; i++) {
                    for (size_t j=0; j<other.col; j++) {
                        for (size_t k=0; k<this->col; k++) {
                            res[i][j] += this->A[i][k]*other[k][j];
                        }
                    }
                }
                return res;
            }

            Matrix& operator*=(const double a) {
                /* 各要素にaをかける */
                for (size_t i=0; i<this->row; i++) {
                    for (size_t j=0; j<this->col; j++) {
                        this->A[i][j] *= a;
                    }
                }
                return *this;
            }
            Matrix operator*(const double a) const {
                return Matrix(*this) *= a;
            }

            void print() {
                /* 行列の状態を表示する */
                string format;
                if (typeid(T)==typeid(int)) format = "%*d"s;
                else if (typeid(T)==typeid(unsigned int) || typeid(T)==typeid(unsigned short)) format = "%*u"s;
                else if (typeid(T)==typeid(long)) format = "%*ld"s;
                else if (typeid(T)==typeid(unsigned long)) format = "%*lu"s;
                else if (typeid(T)==typeid(long long)) format = "%*lld"s;
                else if (typeid(T)==typeid(unsigned long long)) format = "%*llu"s;
                else if (typeid(T)==typeid(short)) format = "%*f"s;
                else if (typeid(T)==typeid(double)) format = "%*lf"s;
                else if (typeid(T)==typeid(long double)) format = "%*LF"s;
                else throw print_format_error();

                int len = 0;
                for (size_t i=0; i<this->row; i++) {
                    for (size_t j=0; j<this->col; j++) {
                        string str = to_string(this->A[i][j]);
                        len = max(len, (int)str.size());
                    }
                }

                printf("[[");
                for (size_t i=0; i<this->row; i++) {
                    for (size_t j=0; j<this->col; j++) {
                        printf(format.c_str(), len, this->A[i][j]);
                        if (j!=this->col-1) printf(", ");
                        else printf("]");
                    }
                    if (i!=this->row-1) printf(",\n  ");
                    else printf("]\n");
                }
            }

            T det() const {
                /* 行列式を計算して返す */
                if (this->row!=this->col) throw determinant_error();

                return this->__cofactor(this->A);
            }

            Matrix dot(const Matrix B) const {
                /* ドット積（内積）計算をする */
                return Matrix(*this) * B;
            }

            Matrix inv() const {
                /* 逆行列を返す（掃き出し法） */
                if (!(this->row==this->col)) throw inversion_error();

                size_t N = this->row;
                Matrix<T> A = *this;
                Matrix<T> invA(N, N);
                for (size_t i=0; i<N; i++) {
                    for (size_t j=0; j<N; j++) {
                        invA[i][j] = (i==j) ? 1 : 0;
                    }
                }

                for (size_t i=0; i<N; i++) {
                    T buf = 1/A[i][i];
                    for (size_t j=0; j<N; j++) {
                        A[i][j] *= buf;
                        invA[i][j] *= buf;
                    }

                    for (size_t j=0; j<N; j++) {
                        if (i!=j) {
                            buf = A[j][i];
                            for (size_t k=0; k<N; k++) {
                                A[j][k] -= A[i][k]*buf;
                                invA[j][k] -= invA[i][k]*buf;
                            }
                        }
                    }
                }

                return invA;
            }
    };
}


void test(){
    cout << "===test===" << endl;
    MatrixLib::Matrix<double> mat1(3,3);
    MatrixLib::Matrix<double> mat2(3,3);
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            mat1[i][j] = j+i*3;
            mat2[i][j] = 1;
        }
    }
    mat2[0][0] = 20;
    mat1 = mat1 + mat2;
    mat1 += mat2;
    mat1.print();
    mat2.print();

    mat1 *= mat2;
    mat1.print();

    mat1 *= 2;
    mat1.print();

    mat1 *= 2.1;
    mat1.print();
}

void test2(){
    cout << "===test2===" << endl;
    MatrixLib::Matrix<int> mat1(2,3);
    MatrixLib::Matrix<int> mat2(3,2);
    mat1[0][0]=2; mat1[0][1]=1; mat1[0][2]=3;
    mat1[1][0]=5; mat1[1][1]=6; mat1[1][2]=4;

    mat2[0][0]=1; mat2[0][1]=2;
    mat2[1][0]=3; mat2[1][1]=2;
    mat2[2][0]=4; mat2[2][1]=3;

    MatrixLib::Matrix<int> mat = mat1 * mat2;
    mat.print();

    mat *= 2;
    mat.print();

    mat *= 2.1;
    mat.print();
}

void test3(){
    cout << "===test3===" << endl;
    MatrixLib::Matrix<int> mat1(3,3);
    MatrixLib::Matrix<int> mat2(3,3);
    mat1[0][0]=2; mat1[0][1]=1; mat1[0][2]=3;
    mat1[1][0]=5; mat1[1][1]=6; mat1[1][2]=4;
    mat1[2][0]=2; mat1[2][1]=1; mat1[2][2]=3;

    mat2[0][0]=1; mat2[0][1]=2; mat2[0][2]=3;
    mat2[1][0]=3; mat2[1][1]=2; mat2[1][2]=2;
    mat2[2][0]=4; mat2[2][1]=3; mat2[2][2]=1;

    mat1.print();
    mat1 *= mat2;
    mat1.print();
}

void test_det2() {
    // 行列式確認用サイト
    // https://keisan.casio.jp/exec/system/1279265553
    cout << "===test_det2===" << endl;
    MatrixLib::Matrix<int> mat(2,2);
    mat[0][0]=3; mat[0][1]=1;
    mat[1][0]=5; mat[1][1]=1;
    mat.print();

    int d = mat.det();
    cout << "Det: " << d << endl;
    // -2
}

void test_det3() {
    cout << "===test_det3===" << endl;
    MatrixLib::Matrix<int> mat(3,3);
    mat[0][0]=3; mat[0][1]=1; mat[0][2]=1;
    mat[1][0]=5; mat[1][1]=1; mat[1][2]=3;
    mat[2][0]=2; mat[2][1]=0; mat[2][2]=1;
    mat.print();

    int d = mat.det();
    cout << "Det: " << d << endl;
    // 2
}

void test_det4() {
    cout << "===test_det4===" << endl;
    MatrixLib::Matrix<int> mat(4,4);
    mat[0][0]=3; mat[0][1]=1; mat[0][2]=1; mat[0][3]=2;
    mat[1][0]=5; mat[1][1]=1; mat[1][2]=3; mat[1][3]=4;
    mat[2][0]=2; mat[2][1]=0; mat[2][2]=1; mat[2][3]=0;
    mat[3][0]=1; mat[3][1]=3; mat[3][2]=2; mat[3][3]=1;
    mat.print();

    int d = mat.det();
    cout << "Det: " << d << endl;
    // -22
}

void test_det5() {
    cout << "===test_det5===" << endl;
    MatrixLib::Matrix<int> mat(5,5);
    mat[0][0]=3; mat[0][1]=1; mat[0][2]=1; mat[0][3]=2; mat[0][4]=1;
    mat[1][0]=5; mat[1][1]=1; mat[1][2]=3; mat[1][3]=4; mat[1][4]=1;
    mat[2][0]=2; mat[2][1]=0; mat[2][2]=1; mat[2][3]=0; mat[2][4]=1;
    mat[3][0]=1; mat[3][1]=3; mat[3][2]=2; mat[3][3]=1; mat[3][4]=1;
    mat[4][0]=1; mat[4][1]=1; mat[4][2]=1; mat[4][3]=1; mat[4][4]=1;
    mat.print();

    int d = mat.det();
    cout << "Det: " << d << endl;
    // -14
}

void test_dot() {
    cout << "===test_dot===" << endl;
    MatrixLib::Matrix<int> mat1(3,3);
    MatrixLib::Matrix<int> mat2(3,3);
    mat1[0][0]=2; mat1[0][1]=1; mat1[0][2]=3;
    mat1[1][0]=5; mat1[1][1]=6; mat1[1][2]=4;
    mat1[2][0]=2; mat1[2][1]=1; mat1[2][2]=3;

    mat2[0][0]=1; mat2[0][1]=2; mat2[0][2]=3;
    mat2[1][0]=3; mat2[1][1]=2; mat2[1][2]=2;
    mat2[2][0]=4; mat2[2][1]=3; mat2[2][2]=1;

    MatrixLib::Matrix<int> res;
    res = mat1.dot(mat2);
    res.print();  // test3と同じ結果になるはず
    mat1.print();
}

void test_inv() {
    // 計算確認用サイト
    // https://keisan.casio.jp/exec/system/1278758206
    cout << "===test_inv===" << endl;
    MatrixLib::Matrix<double> mat(4,4);
    mat[0][0]=3; mat[0][1]=1; mat[0][2]=1; mat[0][3]=2;
    mat[1][0]=5; mat[1][1]=1; mat[1][2]=3; mat[1][3]=4;
    mat[2][0]=2; mat[2][1]=0; mat[2][2]=1; mat[2][3]=0;
    mat[3][0]=1; mat[3][1]=3; mat[3][2]=2; mat[3][3]=1;
    mat.print();

    // 逆行列を計算して出力
    MatrixLib::Matrix<double> inv_mat = mat.inv();
    inv_mat.print();
}

int main(int argc, char const *argv[]){
    test();
    test2();
    test3();
    test_det2();
    test_det3();
    test_det4();
    test_det5();
    test_dot();
    test_inv();
    return 0;
}