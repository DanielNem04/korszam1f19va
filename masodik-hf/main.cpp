#include <iostream>
#include "vector2.h"

int main() {
    Vector2<double> v1{1.0, -1.0};
    Vector2<double> v2{3.0, -1.0};

    std::cout << "v1: " << v1 << "\n";
    std::cout << "v2: " << v2 << "\n";

    auto v3 = v1 + v2;
    std::cout << "v1 + v2 = " << v3 << "\n";

    v1 += v2;
    std::cout << "v1 += v2: " << v1 << "\n";

    auto v4 = v1 * 2.0;
    std::cout << "v1 * 2 = " << v4 << "\n";

    auto v5 = 0.5 * v1;
    std::cout << "0.5 * v1 = " << v5 << "\n";

    auto v6 = v1 / 2.0;
    std::cout << "v1 / 2 = " << v6 << "\n";

    std::cout << "Dot product of v1 and v2: " << dot(v1, v2) << "\n";
    std::cout << "Length of v1: " << length(v1) << "\n";
    std::cout << "Normalized v1: " << normalize(v1) << "\n";

    Vector2<double> inputVec;
    std::cout << "Enter a vector (two numbers): ";
    std::cin >> inputVec;
    std::cout << "You entered: " << inputVec << "\n";

    tensor_product(v1, v2);

    return 0;
}
