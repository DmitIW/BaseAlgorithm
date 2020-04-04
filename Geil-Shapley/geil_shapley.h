//
// Created by Dmitri on 04.04.2020.
//

#ifndef ALGORITHMS_GEIL_SHAPLEY_H
#define ALGORITHMS_GEIL_SHAPLEY_H

#include <unordered_map>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <unordered_set>
#include <list>

class PreferencesTableOrdered {
private:
    std::stack<std::size_t> processingStack;
    std::vector<std::multimap<int, std::size_t>> preferences;
    std::unordered_set<std::size_t> participiants;
public:
    PreferencesTableOrdered() = default;
    explicit PreferencesTableOrdered(std::size_t n);
    std::size_t next();
    void push(std::size_t again);
    void add(std::size_t from, std::size_t to, int pref);
    std::size_t next_candidate(std::size_t n);
    bool all_processed() const;
};

class PreferencesTableUnordered {
private:
    std::vector<std::unordered_map<std::size_t, int>> preferences;
public:
    PreferencesTableUnordered() = default;
    explicit PreferencesTableUnordered(std::size_t n);
    void add(std::size_t from, std::size_t to, int value);
    std::size_t OptimalChoice(std::size_t from, std::size_t first, std::size_t second) const;
};

std::unordered_map<std::size_t, std::size_t> GeilShapleyApply(PreferencesTableOrdered& left,
                                                                  const PreferencesTableUnordered& right);

#endif //ALGORITHMS_GEIL_SHAPLEY_H
