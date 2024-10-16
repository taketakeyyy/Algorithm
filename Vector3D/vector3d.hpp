#include "point3d.hpp"

/**
 * @brief 3次元ベクトル
 *
 */
template<typename T>
class Vector3D {
public:
    T x, y, z;

    Vector3D(T _x, T _y, T _z): x(_x), y(_y), z(_z) {}
    Vector3D(const Point3D<T> &p1, const Point3D<T> &p2): x(p2.x-p1.x), y(p2.y-p1.y), z(p2.z-p1.z) {}

    /**
     * @brief ベクトルの大きさ（L2ノルム）を返す
     *
     * @return double
     */
    double magnitude() const {
        return sqrt(this->magnitude_pow2());
    }

    /**
     * @brief ベクトルの大きさ（L2ノルム）の2乗を返す
     *
     * @return T
     */
    T magnitude_pow2() const {
        return x*x + y*y + z*z;
    }

    /**
     * @brief 内積を計算する
     *
     * @param other
     * @return T
     */
    T inner(const Vector3D &other) const {
        return this->x*other.x + this->y*other.y + this->z*other.z;
    }

    /**
     * @brief 外積を計算する
     *
     * @param other
     * @return Vector3D
     */
    Vector3D cross(const Vector3D &other) const {
        return Vector3D (
            this->y*other.z - this->z*other.y,
            this->z*other.x - this->x*other.z,
            this->x*other.y - this->y*other.x
        );
    }

    bool operator<(const Vector3D &other) const {
        if (this->x < other.x) return true;
        if (this->x == other.x) {
            if (this->y < other.y) return true;
            if (this->y == other.y) {
                return this->z < other.z;
            }
        }
        return false;
    }
    bool operator>(const Vector3D &other) const {
        return other<(*this);
    }
    bool operator==(const Vector3D &other) const {
        return (this->x==other.x) and (this->y==other.y) and (this->z==other.z);
    }
    bool operator<=(const Vector3D &other) const {
        return !(*this > other);
    }
    bool operator>=(const Vector3D &other) const {
        return !(*this < other);
    }
};