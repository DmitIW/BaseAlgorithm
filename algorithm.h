//
// Created by Dmitri on 04.04.2020.
//

#ifndef ALGORITHMS_ALGORITHM_H
#define ALGORITHMS_ALGORITHM_H

#ifdef __cplusplus
extern "C" {
#endif
void PrintAlgorithmNames(void);
//
// Гейл Шейпли
//
void init_geil_shapley(uint32_t pair_count);
void geil_shapley_add_prefernce_left(uint32_t from, uint32_t to, int value);
void geil_shapley_add_prefernce_right(uint32_t from, uint32_t to, int value);
uint64_t* geil_shapley_apply(void);
void cleanup_geil_shapley(uint64_t*);
#ifdef __cplusplus
}
#endif
#endif //ALGORITHMS_ALGORITHM_H
