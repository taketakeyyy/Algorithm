#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/**
 * @brief 二次元累積和
 * @example
 * vector<vector<ll>> A // 二次元配列のデータ
 * Ruisekiwa2D R(A);
 * ll res = R.query({y1,x1},{y2,x2}) // [(y1,x1), (y2,x2)] の長方形の区間和を返す
 */
class Ruisekiwa2D {
private:
    vector<vector<ll>> mR; // 累積和

public:
    // デフォルトコンストラクタ
    Ruisekiwa2D() : mR(vector<vector<ll>>()) {}
    // コピーコンストラクタ
    Ruisekiwa2D(const Ruisekiwa2D &rhs) : mR(rhs.mR) {}
    // コピー代入演算子
    Ruisekiwa2D& operator=(const Ruisekiwa2D &rhs) {
        if (this != &rhs) {  // 自己代入でないことを確認
            mR = rhs.mR;
        }
        return *this;
    }
    // コンストラクタ
    Ruisekiwa2D(const vector<vector<ll>> &A) {
        ll H = A.size();
        ll W = A[0].size();
        mR = A;
        // 横方向に累積和
        for(ll i=0; i<H; i++) {
            for(ll j=1; j<W; j++) mR[i][j] += mR[i][j-1];
        }
        // 縦方向に累積和
        for(ll j=0; j<W; j++) {
            for(ll i=1; i<H; i++) mR[i][j] += mR[i-1][j];
        }
    }

    // [(y1,x1), (y2,x2)] の長方形の区間和を返す
    ll query(const pair<ll,ll> &p1, const pair<ll,ll> &p2) {
        ll y1 = p1.first; ll x1 = p1.second;
        ll y2 = p2.first; ll x2 = p2.second;
        if (x1-1<0 and y1-1<0) return mR[y2][x2];
        else if (x1-1<0) return mR[y2][x2] - mR[y1-1][x2];
        else if (y1-1<0) return mR[y2][x2] - mR[y2][x1-1];
        return mR[y2][x2] - mR[y2][x1-1] - mR[y1-1][x2] + mR[y1-1][x1-1];
    }
};


void test1(){
    // 5x10の配列a
    const vector<vector<ll>> A = {
        {1, 0, 1,},
        {2, 0, 2, },
        {3, 0, 3, },
        {-1,-1,-1,},
    };
    ll H = A.size();
    ll W = A[0].size();

    // 二次元累積和作成
    Ruisekiwa2D R(A);

    {// 座標(0,0) ~ 座標(H-1,W-1)の区間和を求める
        ll res = R.query({0,0}, {H-1,W-1});
        cout << res << endl; // 9
    }

    {// 座標(0,0) ~ 座標(0,0)の区間和を求める
        ll res = R.query({0,0}, {0,0});
        cout << res << endl; // 1
    }

    {// 座標(1,2) ~ 座標(2,2)の区間和を求める
        ll res = R.query({1,2}, {2,2});
        cout << res << endl; // 5
    }
}


int main(int argc, char const *argv[]){
    test1();
    return 0;
}