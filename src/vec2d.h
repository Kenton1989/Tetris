#ifndef VEC2D_H
#define VEC2D_H

#include <utility>

template <typename T>
class Vec2D: public std::pair<T, T>
{
public:
    using ValueT = T;
    using PairT = std::pair<ValueT, ValueT>;

    Vec2D(ValueT x = ValueT(), ValueT y = ValueT()): PairT(x, y) {}
    explicit Vec2D(const PairT& pr): PairT(pr) {}

    ValueT x() const { return this->first; }
    ValueT y() const { return this->second; }
    void setX(ValueT x) { this->first = x; }
    void setY(ValueT y) { this->second = y; }
    void setXY(ValueT x, ValueT y) { this->first = x; this->second = y; }

    Vec2D operator+(const Vec2D& other) const {
        return Vec2D(x() + other.x(), y() + other.y());
    }
    Vec2D operator-(const Vec2D& other) const {
        return Vec2D(x() - other.x(), y() - other.y());
    }
    Vec2D operator-() const {
        return Vec2D(-x(), -y());
    }
    Vec2D operator*(ValueT val) const {
        return Vec2D(x()*val, y()*val);
    }

    Vec2D& operator+=(const Vec2D& other) {
        return *this = *this + other;
    }
    Vec2D& operator-=(const Vec2D& other) {
        return *this = *this - other;
    }
    Vec2D& operator*=(ValueT val) {
        return *this = *this * val;
    }
};

template <typename T, typename U>
inline Vec2D<U> operator*(T val, const Vec2D<U>& v) {
    return Vec2D<U>(v.x()*val, v.y()*val);
}


#endif // VEC2D_H
