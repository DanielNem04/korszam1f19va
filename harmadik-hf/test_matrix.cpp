#include "matrix.h"
#include <iostream>
#include <cmath>
#include <cassert>
#include <iomanip>

void print_side_by_side(const Matrix<double>& A, const Matrix<double>& B, const std::string& op) {
    int n = A.size();
    int m = B.size();
    int max_rows = std::max(n, m);

    for (int i = 0; i < max_rows; ++i) {
        if (i < n) {
            std::cout << "|";
            for (int j = 0; j < n; ++j) {
                std::cout << std::setw(4) << A(i, j);
            }
            std::cout << " |";
        } else {
            std::cout << std::string(n * 4 + 3, ' ');
        }

        if (i == max_rows / 2)
            std::cout << "  " << op << "  ";
        else
            std::cout << "     ";

        if (i < m) {
            std::cout << "|";
            for (int j = 0; j < m; ++j) {
                std::cout << std::setw(4) << B(i, j);
            }
            std::cout << " |";
        }
        std::cout << "\n";
    }
}

void print_vector(const std::vector<double>& v, bool column = false) {
    if (column) {
        for (auto x : v)
            std::cout << "|" << std::setw(4) << x << "|\n";
    } else {
        std::cout << "[";
        for (size_t i = 0; i < v.size(); ++i) {
            std::cout << v[i];
            if (i != v.size() - 1) std::cout << ", ";
        }
        std::cout << "]";
    }
}

void test_all() {
    auto run = [](const char* name, auto&& test_fn) {
        std::cout << std::endl;
        try {
            std::cout << "==== " << name << " ====\n";
            test_fn();
            std::cout << "[OK] " << name << "\n";
        } catch (const std::exception& ex) {
            std::cerr << "[FAIL] " << name << ": " << ex.what() << "\n";
        }
    };

    run("Konstruktor, indexelés", [] {
        Matrix<double> A(3, {1.0, 2.0, 3.0, 4.0, 4.0, 5.0, 7.0, 9.0, 2.0});
        A.print();
        assert(A(0, 0) == 1.0);
        assert(A(1, 1) == 4.0);
        A(2, 2) = 42.0;
        if (A(2, 2) != 42.0) throw std::runtime_error("Write index operator failed");
    });

    run("Összeadás", [] {
        Matrix<double> A(2, {1, 2, 3, 4});
        Matrix<double> B(2, {4, 3, 2, 1});
        print_side_by_side(A, B, "+");
        Matrix<double> C = A + B;
        std::cout << "C = A + B:\n"; C.print();
        if (C(0, 0) != 5.0 || C(1, 0) != 5.0) throw std::runtime_error("Addition failed");
    });

    run("Kivonás", [] {
        Matrix<double> A(2, {5, 6, 7, 8});
        Matrix<double> B(2, {1, 2, 3, 4});
        print_side_by_side(A, B, "-");
        Matrix<double> C = A - B;
        std::cout << "C = A - B:\n"; C.print();
        if (C(0, 0) != 4.0 || C(1, 1) != 4.0) throw std::runtime_error("Subtraction failed");
    });

    run("Skalár szorzás", [] {
        Matrix<double> A(2, {1, 2, 3, 4});
        A = A * 2.0;
        std::cout << "A * 2:\n"; A.print();
        if (A(0, 0) != 2.0 || A(1, 1) != 8.0) throw std::runtime_error("Scalar multiplication failed");
    });

    run("Skalár osztás", [] {
        Matrix<double> A(2, {2, 4, 6, 8});
        A = A / 2.0;
        std::cout << "A / 2:\n"; A.print();
        if (A(0, 1) != 2.0 || A(1, 1) != 4.0) throw std::runtime_error("Scalar division failed");
    });

    run("Mátrix szorzás", [] {
        Matrix<double> A(2, {1, 2, 3, 4});
        Matrix<double> B(2, {2, 0, 1, 2});
        print_side_by_side(A, B, "*");
        Matrix<double> C = A * B;
        std::cout << "C = A * B:\n"; C.print();
        if (C(0, 0) != 4.0 || C(1, 1) != 8.0) throw std::runtime_error("Matrix multiplication failed");
    });

    run("Inverz", [] {
        Matrix<double> A(2, {4, 7, 2, 6});
        std::cout << "A mátrix:\n"; A.print();
        Matrix<double> Ainv = A.inv();
        std::cout << "A^-1:\n"; Ainv.print();
    });

    run("Mátrix osztás", [] {
        Matrix<double> A(2, {4, 7, 2, 8});
        Matrix<double> B(2, {4, 7, 2, 6});
        print_side_by_side(A, B, "/");
        Matrix<double> C = A / B;
        std::cout << "C = A / B:\n"; C.print();
    });

    run("Szép kiírás teszt", [] {
        Matrix<double> A(2, {1, 2, 3, 4});
        std::cout << "A mátrix:\n";
        A.print();
    });

    run("Hibás összeadás (eltérő méret)", [] {
        Matrix<double> A(3, 1.0);
        Matrix<double> B(2, 2.0);
        print_side_by_side(A, B, "+");
        Matrix<double> C = A + B;
        C.print();
    });

    run("Determináns", [] {
        Matrix<double> A(3, {6, 1, 1, 4, -2, 5, 2, 8, 7});
        A.print();
        double det = A.determinant();
        std::cout << "det(A) = " << det << "\n";
        if (std::abs(det - -306.0) > 1e-6) throw std::runtime_error("Determinant incorrect");
    });

    run("Transzponálás", [] {
        Matrix<double> A(2, {1, 2, 3, 4});
        A.print();
        Matrix<double> At = A.transpose();
        std::cout << "A^T:\n";
        At.print();
        if (At(0, 1) != 3.0 || At(1, 0) != 2.0) throw std::runtime_error("Transpose incorrect");
    });

    run("Identitás mátrix", [] {
        Matrix<double> I = Matrix<double>::identity(3);
        I.print();
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (I(i, j) != (i == j ? 1.0 : 0.0))
                    throw std::runtime_error("Identity matrix incorrect");
    });
    run("Vektor szorzás (balról)", [] {
        Matrix<double> A(2, {1, 2, 3, 4});
        std::vector<double> v = {1, 1};
        std::cout << "A mátrix:\n"; A.print();
        std::cout << "v vektor (oszlopként):\n"; print_vector(v, true);
        std::vector<double> res = A * v;
        std::cout << "A * v = "; print_vector(res); std::cout << "\n";
        if (res[0] != 3.0 || res[1] != 7.0)
            throw std::runtime_error("Matrix * vector failed");
    });

    run("Vektor szorzás (jobbról)", [] {
        Matrix<double> A(2, {1, 2, 3, 4});
        std::vector<double> v = {1, 1};
        std::cout << "v vektor (sorként): "; print_vector(v); std::cout << "\n";
        std::cout << "A mátrix:\n"; A.print();
        std::vector<double> res = v * A;
        std::cout << "v * A = "; print_vector(res); std::cout << "\n";
        if (res[0] != 4.0 || res[1] != 6.0)
            throw std::runtime_error("Vector * matrix failed");
    });

    run("Tenzor szorzás (Kronecker)", [] {
        Matrix<double> A(2, {1, 2, 3, 4});
        Matrix<double> B(2, {0, 5, 6, 7});
        std::cout << "A mátrix:\n"; A.print();
        std::cout << "B mátrix:\n"; B.print();
        Matrix<double> T = tensor(A, B);
        std::cout << "A ⊗ B:\n"; T.print();
        if (T.size() != 4) throw std::runtime_error("Tensor product size incorrect");
        if (T(0, 1) != 5 || T(3, 3) != 28) throw std::runtime_error("Tensor product values incorrect");
    });
}

int main() {
    test_all();
    return 0;
}
