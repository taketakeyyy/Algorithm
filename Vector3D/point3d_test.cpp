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

#include "point3d.hpp"

/**
 * @brief ソートのテスト
 *
 */
void test_sort() {
    cout << "===test_sort===" << endl;
    const ll N = 6;
    vector<Point3D<ll>> P(N);
    P[0] = Point3D<ll>(1,1,1);
    P[1] = Point3D<ll>(1,1,1);
    P[2] = Point3D<ll>(-1,1,1);
    P[3] = Point3D<ll>(1,1,2);
    P[4] = Point3D<ll>(1,2,1);
    P[5] = Point3D<ll>(2,0,0);
    sort(P.begin(), P.end());

    // 出力
    for(ll i=0; i<N; i++) {
        printf("(%lld, %lld, %lld)\n", P[i].x, P[i].y, P[i].z);
    }

    assert(P[0].x==-1 and P[0].y==1 and P[0].z==1);
    assert(P[5].x==2 and P[5].y==0 and P[5].z==0);
}


int main() {
    test_sort();
    return 0;
}