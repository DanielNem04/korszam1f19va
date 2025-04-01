#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>

/*
 Kivételosztály mátrixméret-ellenőrzéshez
 Ha két mátrix mérete eltér, ezt dobjuk
*/
class MatrixSizeMismatch : public std::runtime_error {
public:
    MatrixSizeMismatch() : std::runtime_error("Matrix size mismatch") {}
};

/*
 Méretellenőrző függvény
 Két mátrix méretét hasonlítja össze, és kivételt dob, ha nem egyeznek
*/
inline void check_same_size(int a, int b) {
    if (a != b)
        throw MatrixSizeMismatch();
}

/*
 Szépen formázott mátrix kiírás segédfüggvénye
*/
template<typename T>
void print_matrix(const std::vector<T>& data, int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << "|";
        for (int j = 0; j < n; ++j) {
            std::cout << data[i * n + j];
            if (j != n - 1) std::cout << " ";
        }
        std::cout << "|\n";
    }
}

/*
 Négyzetes mátrix osztály sablonnal
 Típusfüggetlen (pl. double, int)
 Tárolás sorfolytonos std::vector-ben
*/
template<typename T>
class Matrix {
    std::vector<T> data_;  // Az adatok tárolása
    int n_;                // A mátrix mérete: n x n

public:
    Matrix(int n, T const& val = T{}) : data_(n * n, val), n_(n) {}

    Matrix(int n, std::initializer_list<T> const& il) : data_(il), n_(n) {
        if (data_.size() != static_cast<size_t>(n_ * n_))
            throw std::runtime_error("Initializer list size mismatch");
    }

    T& operator()(int i, int j) { return data_[i * n_ + j]; }
    T const& operator()(int i, int j) const { return data_[i * n_ + j]; }

    int size() const { return n_; }

    Matrix<T>& operator+=(Matrix<T> const& other) {
        check_same_size(n_, other.n_);
        for (int i = 0; i < n_ * n_; ++i) data_[i] += other.data_[i];
        return *this;
    }

    Matrix<T>& operator-=(Matrix<T> const& other) {
        check_same_size(n_, other.n_);
        for (int i = 0; i < n_ * n_; ++i) data_[i] -= other.data_[i];
        return *this;
    }

    Matrix<T>& operator*=(T const& s) {
        for (std::size_t i = 0; i < data_.size(); ++i) data_[i] *= s;
        return *this;
    }

    Matrix<T>& operator/=(T const& s) {
        for (std::size_t i = 0; i < data_.size(); ++i) data_[i] /= s;
        return *this;
    }

    Matrix<T> inv() const {
        Matrix<T> a = *this;
        Matrix<T> inv(n_, T{});
        for (int i = 0; i < n_; ++i) inv(i, i) = 1;

        for (int i = 0; i < n_; ++i) {
            T pivot = a(i, i);
            if (std::abs(pivot) < 1e-12)
                throw std::runtime_error("Matrix is singular");

            for (int j = 0; j < n_; ++j) {
                a(i, j) /= pivot;
                inv(i, j) /= pivot;
            }

            for (int k = 0; k < n_; ++k) {
                if (k == i) continue;
                T factor = a(k, i);
                for (int j = 0; j < n_; ++j) {
                    a(k, j) -= factor * a(i, j);
                    inv(k, j) -= factor * inv(i, j);
                }
            }
        }
        return inv;
    }

    Matrix<T> transpose() const {
        Matrix<T> result(n_);
        for (int i = 0; i < n_; ++i)
            for (int j = 0; j < n_; ++j)
                result(j, i) = (*this)(i, j);
        return result;
    }

    T determinant() const {
        Matrix<T> temp = *this;
        T det = 1;

        for (int i = 0; i < n_; ++i) {
            int pivot_row = i;
            for (int k = i + 1; k < n_; ++k) {
                if (std::abs(temp(k, i)) > std::abs(temp(pivot_row, i)))
                    pivot_row = k;
            }
            if (std::abs(temp(pivot_row, i)) < 1e-12)
                return 0;

            if (i != pivot_row) {
                for (int j = 0; j < n_; ++j)
                    std::swap(temp(i, j), temp(pivot_row, j));
                det = -det;
            }

            det *= temp(i, i);
            for (int k = i + 1; k < n_; ++k) {
                T factor = temp(k, i) / temp(i, i);
                for (int j = 0; j < n_; ++j)
                    temp(k, j) -= factor * temp(i, j);
            }
        }
        return det;
    }

    static Matrix<T> identity(int n) {
        Matrix<T> id(n);
        for (int i = 0; i < n; ++i)
            id(i, i) = T{1};
        return id;
    }

    void print() const {
        print_matrix(data_, n_);
    }

    friend std::ostream& operator<<(std::ostream& os, Matrix<T> const& m) {
        for (int i = 0; i < m.n_; ++i) {
            os << "|";
            for (int j = 0; j < m.n_; ++j) {
                os << m(i, j);
                if (j != m.n_ - 1) os << " ";
            }
            os << "|\n";
        }
        return os;
    }

    // Mátrix-mátrix és skalár műveletek
    friend Matrix<T> operator+(Matrix<T> a, Matrix<T> const& b) {
        check_same_size(a.n_, b.n_);
        return a += b;
    }

    friend Matrix<T> operator-(Matrix<T> a, Matrix<T> const& b) {
        check_same_size(a.n_, b.n_);
        return a -= b;
    }

    friend Matrix<T> operator*(Matrix<T> a, T const& s) {
        return a *= s;
    }

    friend Matrix<T> operator*(T const& s, Matrix<T> a) {
        return a *= s;
    }

    friend Matrix<T> operator/(Matrix<T> a, T const& s) {
        return a /= s;
    }

    friend Matrix<T> operator*(Matrix<T> const& a, Matrix<T> const& b) {
        check_same_size(a.n_, b.n_);
        int n = a.n_;
        Matrix<T> result(n);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                for (int k = 0; k < n; ++k)
                    result(i, j) += a(i, k) * b(k, j);
        return result;
    }

    friend Matrix<T> operator/(Matrix<T> const& a, Matrix<T> const& b) {
        check_same_size(a.n_, b.n_);
        return a * b.inv();
    }

    // Mátrix * vektor
    friend std::vector<T> operator*(Matrix<T> const& m, std::vector<T> const& v) {
        if (m.n_ != static_cast<int>(v.size()))
            throw MatrixSizeMismatch();
        std::vector<T> result(m.n_, T{});
        for (int i = 0; i < m.n_; ++i)
            for (int j = 0; j < m.n_; ++j)
                result[i] += m(i, j) * v[j];
        return result;
    }

    // Vektor * mátrix
    friend std::vector<T> operator*(std::vector<T> const& v, Matrix<T> const& m) {
        if (m.n_ != static_cast<int>(v.size()))
            throw MatrixSizeMismatch();
        std::vector<T> result(m.n_, T{});
        for (int j = 0; j < m.n_; ++j)
            for (int i = 0; i < m.n_; ++i)
                result[j] += v[i] * m(i, j);
        return result;
    }

    // Tenzorszorzás (Kronecker-szorzat)
    friend Matrix<T> tensor(Matrix<T> const& A, Matrix<T> const& B) {
        int n1 = A.n_, n2 = B.n_;
        Matrix<T> result(n1 * n2);
        for (int i = 0; i < n1; ++i)
            for (int j = 0; j < n1; ++j)
                for (int k = 0; k < n2; ++k)
                    for (int l = 0; l < n2; ++l)
                        result(i * n2 + k, j * n2 + l) = A(i, j) * B(k, l);
        return result;
    }
};
