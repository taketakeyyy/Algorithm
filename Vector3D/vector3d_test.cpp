#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
const long long INF = LONG_LONG_MAX - 1'001'001'001'001'001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };
//ordered_set
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#include "vector3d.hpp"

// ベクトルABとベクトルACの外積が、z軸方向で上向きか調べる
bool is_z_plus (Point3D<ll> A, Point3D<ll> B, Point3D<ll> C) {
    Vector3D<ll> AB(A,B);
    Vector3D<ll> AC(A,C);
    // AB x AC の外積
    auto cp = AB.cross(AC);
    return cp.z > 0;
}

/**
 * @brief https://atcoder.jp/contests/abc266/tasks/abc266_c
 * 入力例1
 *
 */
void test1() {
    cout << "===test1===" << endl;
    // 四角形の4点作る
    Point3D<ll> A(0,0,0);
    Point3D<ll> B(1,0,0);
    Point3D<ll> C(1,1,0);
    Point3D<ll> D(0,1,0);

    // 四角形が凸か調べる
    bool res = true;
    res &= is_z_plus(A,B,C);
    res &= is_z_plus(B,C,D);
    res &= is_z_plus(C,D,A);
    res &= is_z_plus(D,A,B);
    if (res) cout << "Yes" << endl;
    else cout << "No" << endl;
    // Yes
    assert(res == true);
}

/**
 * @brief https://atcoder.jp/contests/abc266/tasks/abc266_c
 * 入力例2
 *
 */
void test2() {
    cout << "===test2===" << endl;
    // 四角形の4点作る
    Point3D<ll> A(0,0,0);
    Point3D<ll> B(1,1,0);
    Point3D<ll> C(-1,0,0);
    Point3D<ll> D(1,-1,0);

    // 四角形が凸か調べる
    bool res = true;
    res &= is_z_plus(A,B,C);
    res &= is_z_plus(B,C,D);
    res &= is_z_plus(C,D,A);
    res &= is_z_plus(D,A,B);
    if (res) cout << "Yes" << endl;
    else cout << "No" << endl;
    // No
    assert(res == false);
}

int main() {
    test1();
    test2();
    return 0;
}