#include "comp6771/euclidean_vector.hpp"
#include <iostream>
#include <sstream>

// Please note: it's not good practice to test your code via a main function that does
//  printing. Instead, you should be using your test folder. This file should only really
//  be used for more "primitive" debugging as we know that working solely with test
//  frameworks might be overwhelming for some.

auto main() -> int {
    std::vector<double> v = {1, 2, 3, 4};
    auto a1 = comp6771::euclidean_vector{3, 4, 5};
    auto a2 = comp6771::euclidean_vector{1, 2, 3};
    std::cout << dot(a1, a2) << "\n";
    (void) a1;
    (void) a2;
}
