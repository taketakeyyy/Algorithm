#ifndef CONVEXHULL_HPP
#define CONVEXHULL_HPP
#include <vector>
#include <stack>

#include "point3d.hpp"
#include "vector3d.hpp"


/**
 * @brief Graham Scanで凸包を求める
 * 計算量O(NlogN)
 *
 * @tparam T Point3Dの型
 * @param points 点のリスト
 * @return std::vector<Point3D<T>> 凸包の点（時計回り）
 * @note
 * - 凸包の周りをぐるりと結んだ線分中にある点は、凸包に含まれない
 * - 凸包の点群は2個以下のときもある。その場合線分だったり、1点だったりする。
 * @example
 * vector<Point3D<ll>> P(N);
 * // ...Pには点群が格納されている
 *
 * // 凸包を求める
 * auto hull = convexHull<ll>(P);
 */
template<typename T>
std::vector<Point3D<T>> convexHull(std::vector<Point3D<T>> points) {
    T n = points.size();
    if (n <= 2) return points;

    // 最も左の点（x座標が最小）を探し、基準点p0に設定
    std::sort(points.begin(), points.end());
    Point3D<T> p0 = points[0];

    // ベクトルPAとPBの外積が、右ねじで時計回り(2)か、反時計回り(1)か、同一直線上(0)か調べる
    auto orientation = [](const Point3D<T> &p, const Point3D<T> &a, const Point3D<T> &b) -> int {
        Vector3D<T> PA(p,a);
        Vector3D<T> PB(p,b);
        auto cp = PA.cross(PB);
        if (cp.z == 0) return 0; // 同一直線上
        return (cp.z > 0) ? 1 : 2; // 反時計回り:1, 時計回り2
    };

    // 点p0から見た点の偏角でソートする用の関数
    auto compareAngle = [&p0, &orientation](const Point3D<T> &a, const Point3D<T> &b) -> bool {
        int o = orientation(p0, a, b);
        Vector3D<T> PA(p0,a);
        Vector3D<T> PB(p0,b);
        if (o == 0) return PA.magnitude_pow2() < PB.magnitude_pow2(); // 一直線上の場合、距離が短い方を優先
        return (o == 1);
    };

    // p0からの偏角でソート
    std::sort(points.begin()+1, points.end(), compareAngle);

    // 凸包を形成する
    std::stack<Point3D<T>> hull; // 凸包候補を格納
    for (T i=0; i<n; i++) {
        if (hull.size() < 2) {
            hull.push(points[i]);
            continue;
        }

        while (hull.size() >= 2) {
            // スタックから2個頂点を取り出して、注目点からのベクトルで凸包に入れるか判定する
            Point3D<T> a = hull.top(); hull.pop();
            const Point3D<T> &b = hull.top();
            const Point3D<T> &p = points[i]; // 注目点

            int o = orientation(p, a, b);
            if (o==2) {
                hull.push(a);
                break;
            }
        }
        hull.push(points[i]);
    }

    // 凸包の点を返す
    std::vector<Point3D<T>> res;
    while (!hull.empty()) {
        res.push_back(hull.top());
        hull.pop();
    }

    return res;
}

#endif //CONVEXHULL_HPP