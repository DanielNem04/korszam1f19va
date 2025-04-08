// az #ifndef #define és #endif header guard helyett:
#pragma once

#include <cmath>
#include <iostream>

template<typename T>
struct Vector2 {
    T x, y;

    Vector2() : x(0), y(0) {}
    Vector2(T x_, T y_) : x(x_), y(y_) {}

    // Összeadás értékadó változata
    Vector2<T>& operator+=(const Vector2<T>& v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    // Kivonás értékadó változata
    Vector2<T>& operator-=(const Vector2<T>& v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    // Skalárral szorzás
    Vector2<T>& operator*=(const T& scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    // Skalárral osztás
    Vector2<T>& operator/=(const T& scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }
};

// Összeadás
template<typename T>
Vector2<T> operator+(const Vector2<T>& a, const Vector2<T>& b) {
    return Vector2<T>{ a.x + b.x, a.y + b.y };
}

// Kivonás
template<typename T>
Vector2<T> operator-(const Vector2<T>& a, const Vector2<T>& b) {
    return Vector2<T>{ a.x - b.x, a.y - b.y };
}

// Skalárral szorzás (jobbról)
template<typename T>
Vector2<T> operator*(const Vector2<T>& v, const T& scalar) {
    return Vector2<T>{ v.x * scalar, v.y * scalar };
}

// Skalárral szorzás (balról)
template<typename T>
Vector2<T> operator*(const T& scalar, const Vector2<T>& v) {
    return v * scalar;
}

// Skalárral osztás
template<typename T>
Vector2<T> operator/(const Vector2<T>& v, const T& scalar) {
    return Vector2<T>{ v.x / scalar, v.y / scalar };
}

// Skaláruis szorzat
template<typename T>
T dot(const Vector2<T>& a, const Vector2<T>& b) {
    return a.x * b.x + a.y * b.y;
}

// Hossznégyzet
template<typename T>
T sqlength(const Vector2<T>& v) {
    return dot(v, v);
}

// Hossz
template<typename T>
T length(const Vector2<T>& v) {
    return std::sqrt(sqlength(v));
}

// Normalizálás
template<typename T>
Vector2<T> normalize(const Vector2<T>& v) {
    return v / length(v);
}

// Kiíró operátor
template<typename T>
std::ostream& operator<<(std::ostream& o, const Vector2<T>& v) {
    o << "[" << v.x << "; " << v.y << "]" ;
    return o;
}

// Beolvasó operátor
template<typename T>
std::istream& operator>>(std::istream& i, Vector2<T>& v) {
    i >> v.x >> v.y;
    return i;
}


// Diadikus / tenzorszorzat (külső szorzat)
template<typename T>
void tensor_product(const Vector2<T>& a, const Vector2<T>& b) {
    std::cout << "Tensor (outer product) of " << a << " and " << b << ":\n";
    std::cout << "[[" << a.x * b.x << " " << a.x * b.y << "]\n";
    std::cout << " [" << a.y * b.x << " " << a.y * b.y << "]]\n";
}
