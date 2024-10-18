#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const long long INF = LONG_LONG_MAX - 1'001'001'001'001'001;

#include "convexhull.hpp"


void test1() {
    cout << "===test1===" << endl;
    vector<Point3D<int>> points = {{0,3,0}, {2,3,0}, {1,1,0}, {2,1,0}, {3,0,0}, {0,0,0}, {3,3,0}};
    vector<Point3D<int>> hull = convexHull<int>(points);

    cout << "Points of convex-hull:\n";
    for (auto point : hull) cout << "(" << point.x << ", " << point.y << ")\n";
    // (0, 3)
    // (2, 3)
    // (3, 3)
    // (3, 0)
    // (0, 0)
}

/**
 * @brief AOJの問題：https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0068
 *
 */
void test_aoj0068_1() {
    cout << "===test_aoj0068_1===" << endl;
    // [入力]
    // 4
    // 1.0,0.0
    // 0.0,1.0
    // 2.0,1.0
    // 1.0,2.0
    ll N = 4;
    vector<Point3D<double>> P(N);
    P[0] = Point3D<double>(1.0, 0.0, 0.0);
    P[1] = Point3D<double>(0.0, 1.0, 0.0);
    P[2] = Point3D<double>(2.0, 1.0, 0.0);
    P[3] = Point3D<double>(1.0, 2.0, 0.0);

    // 凸包を求める
    auto hull = convexHull<double>(P);
    ll ans = N-(ll)hull.size(); // 凸包でない点の個数
    cout << ans << endl;
    // 0
    assert(ans == 0);
}

/**
 * @brief AOJの問題：https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0068
 *
 */
void test_aoj0068_2() {
    cout << "===test_aoj0068_2===" << endl;
    // [入力]
    // 9
    // -509.94,892.63
    // 567.62,639.99
    // -859.32,-64.84
    // -445.99,383.69
    // 667.54,430.49
    // 551.12,828.21
    // -940.2,-877.2
    // -361.62,-970
    // -125.42,-178.48
    ll N = 9;
    vector<Point3D<double>> P(N);
    P[0] = Point3D<double>(-509.94, 892.63, 0.0);
    P[1] = Point3D<double>(567.62, 639.99, 0.0);
    P[2] = Point3D<double>(-859.32, -64.84, 0.0);
    P[3] = Point3D<double>(-445.99, 383.69, 0.0);
    P[4] = Point3D<double>(667.54, 430.49, 0.0);
    P[5] = Point3D<double>(551.12, 828.21, 0.0);
    P[6] = Point3D<double>(-940.2, -877.2, 0.0);
    P[7] = Point3D<double>(-361.62, -970, 0.0);
    P[8] = Point3D<double>(-125.42, -178.48, 0.0);

    // 凸包を求める
    auto hull = convexHull<double>(P);
    ll ans = N-(ll)hull.size(); // 凸包でない点の個数
    cout << ans << endl;
    // 3
    assert(ans == 3);
}

/**
 * @brief Library Checker: https://judge.yosupo.jp/problem/static_convex_hull
 *
 */
void test_static_convex_hull_1() {
    cout << "===test_static_convex_hull_1===" << endl;
    // [入力]
    // 9
    // 0 0
    // 0 1
    // 0 2
    // 1 0
    // 1 1
    // 1 2
    // 2 0
    // 2 1
    // 2 2
    const ll N = 9;
    vector<Point3D<ll>> P(N);
    P[0] = Point3D<ll>(0, 0, 0);
    P[1] = Point3D<ll>(0, 1, 0);
    P[2] = Point3D<ll>(0, 2, 0);
    P[3] = Point3D<ll>(1, 0, 0);
    P[4] = Point3D<ll>(1, 1, 0);
    P[5] = Point3D<ll>(1, 2, 0);
    P[6] = Point3D<ll>(2, 0, 0);
    P[7] = Point3D<ll>(2, 1, 0);
    P[8] = Point3D<ll>(2, 2, 0);

    // 凸包を求める
    auto hull = convexHull<ll>(P);

    // 凸包は時計回りに格納されているので、reverseして出力
    reverse(hull.begin(), hull.end());
    for(ll i=0; i<(ll)hull.size(); i++) printf("%lld %lld\n", hull[i].x, hull[i].y);
    // 0 0
    // 2 0
    // 2 2
    // 0 2
    assert(hull[0] == Point3D<ll>(0,0,0));
    assert(hull[1] == Point3D<ll>(2,0,0));
    assert(hull[2] == Point3D<ll>(2,2,0));
    assert(hull[3] == Point3D<ll>(0,2,0));
}

int main() {
    test1();
    test_aoj0068_1();
    test_aoj0068_2();
    test_static_convex_hull_1();
    return 0;
}