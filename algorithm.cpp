//
// Created by Dmitri on 04.04.2020.
//

#include <iostream>
#include <memory>

#include "algorithm.h"
#include "Geil-Shapley/geil_shapley.h"

void PrintAlgorithmNames(void) {
    std::cout << "Geil-Shapley" << std::endl;
}

static std::unique_ptr<PreferencesTableOrdered> left;
static std::unique_ptr<PreferencesTableUnordered> right;
template<class Table>
static void init(std::unique_ptr<Table>& table, int pair_count) {
    if (table)
        table.reset(nullptr);
    table = std::make_unique<Table>(pair_count);
}
void init_geil_shapley(uint32_t pair_count) {
    init(left, pair_count);
    init(right, pair_count);
}
void geil_shapley_add_prefernce_left(uint32_t from, uint32_t to, int value) { left->add(from, to, -1*value); }
void geil_shapley_add_prefernce_right(uint32_t from, uint32_t to, int value) { right->add(from, to, -1*value); }
static uint64_t* _geil_shapley_apply() {
    auto result = GeilShapleyApply(*left, *right);
    auto* result_as_array = (uint64_t*)malloc(2 * result.size() * sizeof(uint64_t));
    int index = 0;
    for (const auto& pair : result) {
        result_as_array[index] = pair.first;
        result_as_array[result.size() + index] = pair.second;
        index++;
    }
    return result_as_array;
}
uint64_t* geil_shapley_apply(void) {
    return _geil_shapley_apply();
}

void cleanup_geil_shapley(uint64_t* result_as_array) {
    free((void*)result_as_array);
    left.reset(nullptr);
    right.reset(nullptr);
}