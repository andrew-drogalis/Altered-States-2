// Copyright 2024 Andrew Drogalis
// GNU License
#include "optimize-matrix.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_set>

#include "state_populations.hpp"
// inline constexpr int numStates defined in "state-populations"
// inline constexpr std::array<std::pair<std::string_view, int> numStates> statesPopulation defined in
// "state-populations"

namespace alteredstates
{

constexpr int numChars {26};
constexpr int minThreshold {165'379'868};

Optimizer::Optimizer(std::string& defaultMatrix) : defaultMatrix(defaultMatrix) {}

int Optimizer::calculateScore(int matrixSize, std::string const& resultsMatrixStr)
{
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
                if (level < lenStateWord && state[level] != resultsMatrixStr[index])
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

void Optimizer::maximizeScore()
{
    int totalLength      = defaultMatrix.length();
    int const matrixSize = std::sqrt(totalLength);
    assert(totalLength == matrixSize * matrixSize);

    int maxScore {};
    std::unordered_set<std::string_view> maxStatesVisited;
    // Switch and / or Alter Two Positions
    for (int strIndex1 {}; strIndex1 < totalLength; ++strIndex1)
    {
        for (int chIndex {}; chIndex < numChars; ++chIndex)
        {
            // Letter "Q" Not in Any US State
            if (chIndex == 'q' - 'a')
            {
                ++chIndex;
            }
            for (int strIndex2 {strIndex1 + 1}; strIndex2 < totalLength; ++strIndex2)
            {
                for (int chIndex2 {}; chIndex2 < numChars; ++chIndex2)
                {
                    if (chIndex2 == 'q' - 'a')
                    {
                        ++chIndex2;
                    }
                    std::string newMatrix = defaultMatrix;
                    newMatrix[strIndex1]  = static_cast<char>('a' + chIndex);
                    newMatrix[strIndex2]  = static_cast<char>('a' + chIndex2);

                    statesVisited  = {};
                    int totalScore = calculateScore(matrixSize, newMatrix);

                    if (totalScore > maxScore)
                    {
                        maxScore         = totalScore;
                        maxStatesVisited = statesVisited;
                        resultMatrix     = newMatrix;
                    }
                }
            }
        }
    }
    if (maxScore >= minThreshold)
    {
        std::cout << "Congratulations! Your Score of " << maxScore << " Passed!\n";
        // Extra Achievements
        if (maxScore >= 200'000'000)
        {
            std::cout << "Awarded 200 Million Achievement!\n";
        }
        if (! maxStatesVisited.contains("california"))
        {
            std::cout << "Awarded 'No California' Achievement!\n";
        }
        if (maxStatesVisited.contains("pennsylvania"))
        {
            std::cout << "Awarded 'Visited Pennsylvania' Achievement!\n";
        }
        if (maxStatesVisited.size() >= 20)
        {
            std::cout << "Awarded 'Visited 20 States' Achievement!\n";
        }
        if (maxStatesVisited.contains("colorado") && maxStatesVisited.contains("utah") &&
            maxStatesVisited.contains("arizona") && maxStatesVisited.contains("newmexico"))
        {
            std::cout << "Awarded 'Visited All 4 Corner States' Achievement\n!";
        }
        int mCount {};
        for (auto const& state : maxStatesVisited)
        {
            if (state[0] == 'm')
            {
                ++mCount;
            }
        }
        if (mCount == 8)
        {
            std::cout << "Awarded 'Visited All M States' Achievement!\n";
        }
    }
    else
    {
        std::cout << "Your score of " << maxScore << " Didn't pass\n";
    }
}

std::string Optimizer::returnResultMatrix() const noexcept { return resultMatrix; }

}// namespace alteredstates
