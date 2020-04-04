//
// Created by Dmitri on 04.04.2020.
//

#include "geil_shapley.h"

#include <iostream>

//#define __debug

PreferencesTableOrdered::PreferencesTableOrdered(std::size_t n): processingStack(), preferences(), participiants() {
    preferences.assign(n, {});
}
std::size_t PreferencesTableOrdered::next() {
    std::size_t result = processingStack.top();
    processingStack.pop();
    return result;
}
void PreferencesTableOrdered::push(std::size_t again) { processingStack.push(again); }
void PreferencesTableOrdered::add(std::size_t from, std::size_t to, int pref) {
    if (participiants.insert(from).second)
        processingStack.push(from);
    preferences[from].emplace(pref, to);
}
std::size_t PreferencesTableOrdered::next_candidate(std::size_t n) {
    auto& target = preferences[n];
    auto node = target.extract(target.begin());
    return node.mapped();
}
bool PreferencesTableOrdered::all_processed() const { return processingStack.empty(); }

PreferencesTableUnordered::PreferencesTableUnordered(std::size_t n): preferences() {
    preferences.assign(n, {});
}
void PreferencesTableUnordered::add(std::size_t from, std::size_t to, int value) {
    preferences[from].emplace(to, value);
}
std::size_t PreferencesTableUnordered::OptimalChoice(std::size_t from, std::size_t first, std::size_t second) const {
    const auto& target = preferences[from];
    if (target.at(first) >= target.at(second))
        return first;
    return second;
}

std::unordered_map<std::size_t, std::size_t> GeilShapleyApply(PreferencesTableOrdered& left,
                                                              const PreferencesTableUnordered& right) {
    std::unordered_map<std::size_t, std::size_t> potential_pairs{};
    while (!left.all_processed()) {
        std::size_t current = left.next();
        std::size_t target = left.next_candidate(current);
#ifdef __debug
        std::cerr << "Current value:  " << current << std::endl;
        std::cerr << "Current target: " << target << std::endl;
#endif
        if (auto [iter, was_insert] = potential_pairs.emplace(target, current); !was_insert) {
            std::size_t optimal = right.OptimalChoice(target, iter->second, current);
            if (optimal == current)
                left.push(iter->second);
            else
                left.push(current);
            iter->second = optimal;
#ifdef __debug
            std::cerr << "Current optimal: " << iter->second << std::endl;
#endif
        }
    }
#ifdef __debug
    std::cerr << "Gone" << std::endl;
#endif
    return potential_pairs;
}