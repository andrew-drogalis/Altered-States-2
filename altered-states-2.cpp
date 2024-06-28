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

void getConnectionScores()
{
    std::array<std::pair<std::string, double>, numStates> stateAlteredScore {};
    std::array<std::array<double, numChars>, numChars> charAdjacencyScore {};
    std::array<std::array<int, numChars>, numChars> charAdjacencyCount {};
    int i {};

    for (auto [state, population] : statesPopulation)
    {
        stateAlteredScore[i] = std::make_pair(state, 0.0);
        double populationPerChar = population / static_cast<double>(state.length());
        char lastChar            = ' ';
        for (char ch : state)
        {
            int index = ch - 'a';
            if (lastChar != ' ')
            {
                charAdjacencyCount[lastChar - 'a'][index]++;
                charAdjacencyScore[lastChar - 'a'][index] += populationPerChar;
            }
            lastChar = ch;
        }
        ++i;
    }

    std::array<int, numChars> numOfConnections {};
    std::array<double, numChars> connectionsScore {};
    for (int i {}; i < numChars; ++i)
    {
        for (int j {}; j < numChars; ++j)
        {
            if (charAdjacencyCount[i][j])
            {
                numOfConnections[i]++;
                connectionsScore[i] += charAdjacencyScore[i][j];
            }
        }
    }
}

int saveToJSON(std::string const& resultsMatrixStr)
{
    // Save results to file for export to Jane Street for judging
    std::ofstream saveMatrix {"json/result-matrix.txt"};
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
    getConnectionScores();
    std::array<std::array<char, matrixSize>, matrixSize> resultsMatrix = {{'a'}};

    std::string resultsMatrixStr;
    for (auto row : resultsMatrix)
    {
        for (auto col : row) { resultsMatrixStr.push_back(col); }
    }
    return saveToJSON(resultsMatrixStr);
}
