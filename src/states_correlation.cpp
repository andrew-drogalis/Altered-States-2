// Copyright 2024 Andrew Drogalis
// GNU License
#include "states_correlation.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <string>
#include <string_view>
#include <unordered_map>

#include "state_populations.hpp"
// inline constexpr int numStates defined in "state-populations"
// inline std::array<std::pair<std::string_view, int> numStates> statesPopulation defined in
// "state-populations"

namespace alteredstates
{

constexpr int numChars {26};

void StatesCorrelation::statesLetterCorrelation()
{
    std::unordered_map<std::string_view, std::array<int, numChars>> stateCharHashMap;
    for (auto const& [state, population] : statesPopulation)
    {
        std::array<int, numChars> stateChars {};
        for (char ch : state)
        {
            int index = ch - 'a';
            ++stateChars[index];
        }
        stateCharHashMap[state] = stateChars;
    }

    auto sortByValue = [](std::pair<std::string_view, int> A, std::pair<std::string_view, int> B) {
        return A.second < B.second;
    };

    int stateIndex {};
    for (auto const& [state, population] : statesPopulation)
    {
        int index {};
        std::array<std::pair<std::string_view, int>, numStates> stateCharDifference {};
        for (auto const& [stateComp, populationComp] : statesPopulation)
        {
            int totalCharDifference {};
            for (int i {}; i < numChars; ++i)
            {
                totalCharDifference += std::abs(stateCharHashMap[state][i] - stateCharHashMap[stateComp][i]);
            }
            stateCharDifference[index] = std::make_pair(stateComp, totalCharDifference);
            ++index;
        }
        std::sort(stateCharDifference.begin(), stateCharDifference.end(), sortByValue);
        statesCorrelation[stateIndex] = std::make_pair(state, stateCharDifference);
        ++stateIndex;
    }
}

std::string StatesCorrelation::buildStringFromArray() noexcept
{
    std::string arrString = "{";

    for (auto const& [state, arr] : statesCorrelation)
    {
        arrString += "\"" + std::string {state} + "\": {";

        for (auto const& [subState, difference] : arr)
        {
            arrString += "\"" + std::string {subState} + "\":" + std::to_string(difference) + ",";
        }
        arrString += "},";
    }
    arrString += "}";

    return arrString;
}

}// namespace alteredstates
