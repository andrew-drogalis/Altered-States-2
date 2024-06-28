// Copyright 2024 Andrew Drogalis
// GNU License
#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>

#include <functional>
#include <unordered_set>

#include "state-populations.h"
// inline constexpr int numStates defined in "state-populations"
// inline constexpr std::array<std::pair<std::string_view, int> numStates> statesPopulation defined in
// "state-populations"

constexpr int matrixSize {5};
constexpr int numChars {26};

struct Solution
{
    std::string resultMatrix;
    int maxScore {};

    void getLetterOccurrences()
    {
        std::array<std::pair<char, double>, numChars> charOccurrence {};
        double const THRESHOLD = 7.0;
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
                if (charAdjacencyCount[i][j])
                {
                    numOfUniqueConnections[i]++;
                }
            }
            charOccurrence[i] = std::make_pair('a' + i, numOfUniqueConnections[i] / THRESHOLD);
        }

        auto comp = [](std::pair<char, double> A, std::pair<char, double> B) { return A.second < B.second; };

        std::sort(charOccurrence.rbegin(), charOccurrence.rend(), comp);

        for (auto const& [ch, occurrence] : charOccurrence)
        {
            int count = std::round(occurrence);
            if (ch == 'e')
            {
                ++count;
            }
            for (int i {}; i < count; ++i) { resultMatrix.push_back(ch); }
        }
    }

    int calculateScore()
    {
        std::unordered_set<std::string_view> statesVisited;
        int totalScore {};
        // All 8 Directions for Kings moves in chess
        int const numOfDirections {8};
        std::array<int, numOfDirections + 1> directions = {1, 0, -1, 0, 1, 1, -1, -1, 1};

        // Recursive Matrix Navigation
        std::function<void(int, int, int, int, std::array<int, numStates>)> searchMatrix =
            [&](int index, int row, int col, int level, std::array<int, numStates> errorCharCount) {
                int i {};
                bool breakOut = true;
                for (auto const& [state, population] : statesPopulation)
                {
                    int lenStateWord = state.length();
                    if (level < lenStateWord && state[level] != resultMatrix[index])
                    {
                        errorCharCount[i]++;
                    }
                    if (level >= lenStateWord)
                    {
                        errorCharCount[i]++;
                    }
                    // Store the result
                    if (level == lenStateWord - 1 && errorCharCount[i] <= 1 && ! statesVisited.contains(state))
                    {
                        totalScore += population;
                        statesVisited.insert(state);
                    }
                    // If we still have a chance then continue the search
                    if (errorCharCount[i] <= 1)
                    {
                        breakOut = false;
                    }
                    ++i;
                }
                if (breakOut)
                {
                    return;
                }

                for (int i {}; i < numOfDirections; ++i)
                {
                    int nextRow = row + directions[i];
                    int nextCol = col + directions[i + 1];
                    if (nextRow >= 0 && nextCol >= 0 && nextRow < matrixSize && nextCol < matrixSize)
                    {
                        int index = matrixSize * nextRow + nextCol;
                        searchMatrix(index, nextRow, nextCol, level + 1, errorCharCount);
                    }
                }
            };

        // Search through all points in the matrix
        for (int row {}; row < matrixSize; ++row)
        {
            for (int col {}; col < matrixSize; ++col)
            {
                int index = matrixSize * row + col;
                std::array<int, numStates> errorCharCount {};
                searchMatrix(index, row, col, 0, errorCharCount);
            }
        }
        return totalScore;
    }

    void test() {}

    [[nodiscard]] std::string returnResult() const noexcept { return resultMatrix; }
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
    solution.getLetterOccurrences();
    auto resultsMatrix = solution.returnResult();

    return saveToJSON(resultsMatrix);
}
