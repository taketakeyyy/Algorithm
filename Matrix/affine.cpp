#include <bits/stdc++.h>
using namespace std;

/***
 *
 * 2次元座標のアフィン変換
 *
 **/
class Affine {
    private:
        vector<vector<double>> A;
    public:
        Affine() {
            A.resize(3);
            for (int i=0; i<3; i++) A[i].resize(3);

            this->A[0][0]=1.0; this->A[1][1]=1.0; this->A[2][2]=1.0;  // 単位行列
        }

        void zoom(double sx, double sy) {
            /***拡大縮小
             * Args:
             *   sx(double): X軸方向の拡大率
             *   sy(double): Y軸方向の拡大率
             ***/
            vector<vector<double>> B(3, vector<double>(3, 0.0));
            vector<vector<double>> C(3, vector<double>(3, 0.0));
            B[0][0]=sx; B[1][1]=sy; B[2][2]=1.0;
            for (int i=0; i<3; i++) {
                for(int j=0; j<3; j++) {
                    for (int k=0; k<3; k++) {
                        C[i][j] += B[i][k]*this->A[k][j];
                    }
                }
            }
            this->A = C;
        }

        void translate(double tx, double ty) {
            /*** 平行移動
             * Args:
             *  tx(double): X軸方向にtx移動
             *  ty(double): Y軸方向にty移動
             ***/
            vector<vector<double>> B(3, vector<double>(3, 0.0));
            vector<vector<double>> C(3, vector<double>(3, 0.0));
            B[0][0]=1.0; B[1][1]=1.0; B[2][2]=1.0;
            B[0][2]=tx; B[1][2]=ty;
            for (int i=0; i<3; i++) {
                for(int j=0; j<3; j++) {
                    for (int k=0; k<3; k++) {
                        C[i][j] += B[i][k]*this->A[k][j];
                    }
                }
            }
            this->A = C;
        }

        void rotate_rad(double rad) {
            /*** 回転
             * Args:
             *  rad: 角度（ラジアン）
             *
             * Notes:
             *  反時計回りに回転する
             ***/
            vector<vector<double>> B(3, vector<double>(3, 0.0));
            vector<vector<double>> C(3, vector<double>(3, 0.0));
            B[0][0]=cos(rad); B[0][1]=-sin(rad);
            B[1][0]=sin(rad); B[1][1]=cos(rad);
            B[2][2]=1.0;
            for (int i=0; i<3; i++) {
                for(int j=0; j<3; j++) {
                    for (int k=0; k<3; k++) {
                        C[i][j] += B[i][k]*this->A[k][j];
                    }
                }
            }
            this->A = C;
        }

        void rotate_deg(double deg) {
            /*** 回転
             * Args:
             *  deg(double): 角度（度数法）
             *
             * Notes:
             *  反時計回りに回転する
             ***/
            static const double PI = 3.141592653589793;
            this->rotate_rad(deg*PI/180);
        }

        void reflectX(double p) {
            /*** x=pで対称移動
             * Args:
             *  p(double): x=pで対称移動
             ***/
            vector<vector<double>> B(3, vector<double>(3, 0.0));
            vector<vector<double>> C(3, vector<double>(3, 0.0));
            B[0][0]=-1.0; B[0][2]=2*p;
            B[1][1]=1.0;
            B[2][2]=1.0;
            for (int i=0; i<3; i++) {
                for(int j=0; j<3; j++) {
                    for (int k=0; k<3; k++) {
                        C[i][j] += B[i][k]*this->A[k][j];
                    }
                }
            }
            this->A = C;
        }

        void reflectY(double p) {
            /*** y=pで対称移動
             * Args:
             *  p(double): y=pで対称移動
             ***/
            vector<vector<double>> B(3, vector<double>(3, 0.0));
            vector<vector<double>> C(3, vector<double>(3, 0.0));
            B[0][0]=1.0;
            B[1][1]=-1.0; B[1][2]=2*p;
            B[2][2]=1.0;
            for (int i=0; i<3; i++) {
                for(int j=0; j<3; j++) {
                    for (int k=0; k<3; k++) {
                        C[i][j] += B[i][k]*this->A[k][j];
                    }
                }
            }
            this->A = C;
        }

        pair<double, double> calc(double x, double y) {
            /*** 座標計算する
             * Args:
             *  x(double): 変換前のx座標
             *  y(double): 変換前のy座標
             *
             * Returns (pair):
             *  nx(double): 変換後のx座標
             *  ny(double): 変換後のy座標
             ***/
            double nx = this->A[0][0]*x + this->A[0][1]*y + this->A[0][2];
            double ny = this->A[1][0]*x + this->A[1][1]*y + this->A[1][2];
            return make_pair(nx, ny);
        }
};


void test(){
    // ABC189-Eの入力例1を試す
    // https://atcoder.jp/contests/abc189/tasks/abc189_e

    Affine A = Affine();

    // 最初はx=1, y=2
    double x=1.0, y=2.0;
    double nx, ny;
    cout << x << " " << y << endl;  // 1 2

    // 時計回りに90度回転
    A.rotate_deg(-90);
    tie(nx, ny) = A.calc(x, y);
    cout << nx << " " << ny << endl;  // 2 -1

    // x=3で対称な位置に移動
    A.reflectX(3);
    tie(nx, ny) = A.calc(x, y);
    cout << nx << " " << ny << endl;  // 4 -1

    // 反時計回りに90度回転
    A.rotate_deg(90);
    tie(nx, ny) = A.calc(x, y);
    cout << nx << " " << ny << endl;  // 1 4

    // y=2で対称な位置に移動
    A.reflectY(2);
    tie(nx, ny) = A.calc(x, y);
    cout << nx << " " << ny << endl;  // 1 0
}


int main(int argc, char const *argv[]){
    test();
    return 0;
}