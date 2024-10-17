/**
 * @brief 3次元点
 * @example
 * // 点A(1,2,0)を作成
 * Point3D<ll> A(1,2,0);
 */
template<typename T>
struct Point3D {
    T x, y, z;

    bool operator<(const Point3D<T> &other) const {
        if (this->x < other.x) return true;
        if (this->x == other.x) {
            if (this->y < other.y) return true;
            if (this->y == other.y) {
                return this->z < other.z;
            }
        }
        return false;
    }
    bool operator>(const Point3D<T>& other) const {
        return other < *this;
    }
    bool operator==(const Point3D<T> &other) const {
        return (this->x==other.x) and (this->y==other.y) and (this->z==other.z);
    }
    bool operator<=(const Point3D<T>& other) const {
        return !(*this > other);
    }
    bool operator>=(const Point3D<T>& other) const {
        return !(*this < other);
    }
};
