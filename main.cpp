//
// Created by Dmitri on 04.04.2020.
//

#include <iostream>
#include <vector>
#include "algorithm.h"

using namespace std;

int main () {
    PrintAlgorithmNames();
    std::vector<std::string> left {
        "Adam", "Marcus", "Pock", "Tom"
    };
    std::vector<std::string> right {
        "Anna", "Jenny", "Elizabeth", "Marry"
    };

    init_geil_shapley(4);
    for (auto i = 0; i < 4; i++) {
        for (auto j = 0; j < 4; j++) {
            geil_shapley_add_prefernce_left(i, j, 0);
            geil_shapley_add_prefernce_right(j, i, 0);
        }
    }
    auto result = geil_shapley_apply();
    for (int i = 0; i < 4; i++) {
        std::cout << right[result[i]] << " + " << left[result[i+4]] << std::endl;
    }
    cleanup_geil_shapley(result);
    return 0;
}
