// Copyright 2024 Andrew Drogalis
// GNU License
#include <array>
#include <fstream>
#include <iostream>
#include <string>

#include "state-populations.h"
// inline constexpr int numStates defined in "state-populations"
// inline constexpr std::array<std::pair<std::string_view, int> numStates> statesPopulation defined in
// "state-populations"

constexpr int matrixSize {5};
constexpr int numChars {26};

constexpr void charScore()
{
    std::array<double, numChars> charScoreArr;
    std::array<int, numChars> letterCount;
    std::array<std::array<double, numChars>, numChars> charAdjacencyScoreForward;
    std::array<std::array<int, numChars>, numChars> charAdjacencyCountForward;
    std::array<std::array<double, numChars>, numChars> charAdjacencyScoreReverse;
    std::array<std::array<int, numChars>, numChars> charAdjacencyCountReverse;

    for (auto [state, population] : statesPopulation)
    {
        double populationPerChar = population / static_cast<double>(state.length());
        char lastChar            = ' ';
        for (char ch : state)
        {
            int index = ch - 'a';
            letterCount[index]++;
            charScoreArr[index] += populationPerChar;
            if (lastChar != ' ')
            {
                charAdjacencyCountForward[lastChar - 'a'][index]++;
                charAdjacencyScoreForward[lastChar - 'a'][index] += populationPerChar;
                charAdjacencyCountReverse[index][lastChar - 'a']++;
                charAdjacencyScoreReverse[index][lastChar - 'a'] += populationPerChar;
            }
            lastChar = ch;
        }
    }
}

int saveToJSON(std::string const& resultsMatrixStr)
{
    // Save results to file for export to Jane Street for judging
    std::ofstream saveMatrix {"json/result-matrix.json"};
    if (saveMatrix.is_open())
    {
        saveMatrix << resultsMatrixStr;
        if (! saveMatrix.good())
        {
            std::cout << "Error Writing to File";
            return 1;
        }
    }
    else
    {
        std::cout << "Error Opening File";
        return 1;
    }
    return 0;
}

int main()
{
    //
    std::array<std::array<char, matrixSize>, matrixSize> resultsMatrix = {{'a'}};

    std::string resultsMatrixStr;
    for (auto row : resultsMatrix)
    {
        for (auto col : row) { resultsMatrixStr.push_back(col); }
    }
    return saveToJSON(resultsMatrixStr);
}
