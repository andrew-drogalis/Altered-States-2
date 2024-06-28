// Copyright 2024 Andrew Drogalis
// GNU License
#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <string_view>
#include <vector>

#include "state-populations.h"
// inline constexpr int numStates defined in "state-populations"
// inline constexpr std::array<std::pair<std::string_view, int> numStates> statesPopulation defined in
// "state-populations"

constexpr int matrixSize {5};
constexpr int numChars {26};

struct Solution
{
    std::array<std::array<char, matrixSize>, matrixSize> resultMatrix {};
    std::array<int, numChars> numOfUniqueConnections {};
    std::array<double, numChars> connectionsScore {};
    std::array<int, numChars> totalCount {};

    Solution()
    {
        getConnectionScores();
        findBestFitStates();
    }

    void getConnectionScores()
    {

        std::array<std::array<double, numChars>, numChars> charAdjacencyScore {};
        std::array<std::array<int, numChars>, numChars> charAdjacencyCount {};
        for (auto const& [state, population] : statesPopulation)
        {
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
        }

        for (int i {}; i < numChars; ++i)
        {
            for (int j {}; j < numChars; ++j)
            {
                if (charAdjacencyCount[i][j])
                {
                    numOfUniqueConnections[i]++;
                    connectionsScore[i] += charAdjacencyScore[i][j];
                    totalCount[i] += charAdjacencyCount[i][j];
                }
            }
        }
    }

    void findBestFitStates()
    {
        auto comp = [](std::pair<std::string_view, double> A, std::pair<std::string_view, double> B) {
            return A.second < B.second;
        };
        std::vector<std::pair<std::string_view, double>> stateAlteredScore;

        for (auto const& [state, population] : statesPopulation)
        {
            double alteredStateZScore {};
            double minValue = std::numeric_limits<double>::max();
            for (char ch : state)
            {
                alteredStateZScore += connectionsScore[ch - 'a'];
                minValue = std::min(minValue, connectionsScore[ch = 'a']);
            }
            alteredStateZScore -= minValue;
            double wordMeanZScore = alteredStateZScore / static_cast<double>(state.length() - 1);

            stateAlteredScore.emplace_back(state, wordMeanZScore);
        }
        std::sort(stateAlteredScore.rbegin(), stateAlteredScore.rend(), comp);

        for (auto [state, zscore] : stateAlteredScore) { std::cout << state << " " << zscore << '\n'; }
    }

    [[nodiscard]] std::array<std::array<char, matrixSize>, matrixSize> returnResult() const noexcept
    {
        return resultMatrix;
    }
};

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
    Solution solution;
    std::array<std::array<char, matrixSize>, matrixSize> resultsMatrix = solution.returnResult();

    std::string resultsMatrixStr;
    for (auto row : resultsMatrix)
    {
        for (auto col : row) { resultsMatrixStr.push_back(col); }
    }
    return saveToJSON(resultsMatrixStr);
}
