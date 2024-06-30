// Copyright 2024 Andrew Drogalis
// GNU License
#ifndef STATES_CORRELATION_H
#define STATES_CORRELATION_H

#include <string>
#include <string_view>
#include "state_populations.hpp"
// inline constexpr int numStates defined in "state-populations"
// inline std::array<std::pair<std::string_view, int> numStates> statesPopulation defined in
// "state-populations"

namespace alteredstates
{

struct StatesCorrelation
{
    StatesCorrelation() = default;

    void statesLetterCorrelation();

    [[nodiscard]] std::string buildStringFromArray() noexcept;

    std::array<std::pair<std::string_view, std::array<std::pair<std::string_view, int>, numStates>>, numStates>
        statesCorrelation {};
};

}// namespace alteredstates
#endif
