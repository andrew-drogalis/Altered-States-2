// Copyright 2024 Andrew Drogalis
// GNU License
#include "find_letter_occurrences.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <string>
#include <utility>

#include "state_populations.hpp"
// inline constexpr int numStates defined in "state-populations"
// inline constexpr std::array<std::pair<std::string_view, int> numStates> statesPopulation defined in
// "state-populations"

namespace alteredstates
{

constexpr int matrixSize {5};
constexpr int numChars {26};

void LetterOccurrences::findOccurrences()
{
    std::array<std::pair<char, double>, numChars> charOccurrence {};
    std::array<int, numChars> numOfUniqueConnections {};
    std::array<std::array<int, numChars>, numChars> charAdjacencyCount {};
    for (auto const& [state, population] : statesPopulation)
    {
        char lastChar = ' ';
        for (char ch : state)
        {
            int index = ch - 'a';
            if (lastChar != ' ')
            {
                charAdjacencyCount[lastChar - 'a'][index]++;
            }
            lastChar = ch;
        }
    }
    for (int i {}; i < numChars; ++i)
    {
        for (int j {}; j < numChars; ++j)
        {
            std::cout << "Prime: " << char(i + 'a') << " Rel: " << char(j + 'a') << " - " << charAdjacencyCount[i][j]
                      << '\n';
        }
    }

    double const THRESHOLD = 7.0;
    for (int i {}; i < numChars; ++i)
    {
        for (int j {}; j < numChars; ++j)
        {
            if (charAdjacencyCount[i][j])
            {
                numOfUniqueConnections[i]++;
            }
        }
        charOccurrence[i] = std::make_pair('a' + i, numOfUniqueConnections[i] / THRESHOLD);
    }

    auto comp = [](std::pair<char, double> A, std::pair<char, double> B) { return A.second < B.second; };

    std::sort(charOccurrence.rbegin(), charOccurrence.rend(), comp);

    int const INNER_MATRIX_SIZE = 9;
    for (auto const& [ch, occurrence] : charOccurrence)
    {
        int count = std::round(occurrence);
        std::cout << ch << " " << occurrence << '\n';
        if (ch == 'e')
        {
            ++count;
        }
        for (int i {}; i < count; ++i)
        {
            if (resultMatrixInner.length() < INNER_MATRIX_SIZE)
            {
                resultMatrixInner.push_back(ch);
            }
            else
            {
                resultMatrixOuter.push_back(ch);
            }
        }
    }
}

std::string LetterOccurrences::returnResultInner() const noexcept { return resultMatrixInner; }

std::string LetterOccurrences::returnResultOuter() const noexcept { return resultMatrixOuter; }

}// namespace alteredstates
