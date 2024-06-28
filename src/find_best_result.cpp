// Copyright 2024 Andrew Drogalis
// GNU License
#include "find_best_result.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>

#include "state_populations.hpp"
// inline constexpr int numStates defined in "state-populations"
// inline constexpr std::array<std::pair<std::string_view, int> numStates> statesPopulation defined in
// "state-populations"

namespace alteredstates
{

constexpr int minThreshold {165'379'868};

Optimizer::Optimizer(std::string& innerMatrix, std::string& outerMatrix)
    : innerMatrix(innerMatrix), outerMatrix(outerMatrix)
{
}

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
    int totalLength      = innerMatrix.length() + outerMatrix.length();
    int const matrixSize = std::sqrt(totalLength);
    assert(totalLength == matrixSize * matrixSize);

    int maxScore {};
    do {
        statesVisited = {};
        std::string newMatrix;
        int innerPointer {};
        int outerPointer {};
        for (int i {}; i < matrixSize; ++i)
        {
            for (int j {}; j < matrixSize; ++j)
            {
                if (i != 0 && i != matrixSize - 1 && j != 0 && j != matrixSize - 1)
                {
                    newMatrix.push_back(innerMatrix[innerPointer]);
                    ++innerPointer;
                }
                else
                {
                    newMatrix.push_back(outerMatrix[outerPointer]);
                    ++outerPointer;
                }
            }
        }

        int totalScore = calculateScore(matrixSize, newMatrix);

        maxScore = std::max(maxScore, totalScore);
        if (totalScore >= minThreshold)
        {
            // std::cout << "Congratulations! Your Score of " << totalScore << " Passed!\n";
            // // Extra Achievements
            // if (totalScore >= 200'000'000)
            // {
            //     std::cout << "Awarded 200 Million Achievement!";
            // }
            // if (! statesVisited.contains("california"))
            // {
            //     std::cout << "Awarded 'No California' Achievement!";
            // }
            // if (statesVisited.contains("pennsylvania"))
            // {
            //     std::cout << "Awarded 'Visited Pennsylvania' Achievement!";
            // }
            // if (statesVisited.size() >= 20)
            // {
            //     std::cout << "Awarded 'Visited 20 States' Achievement!";
            // }
            // if (statesVisited.contains("colorado") && statesVisited.contains("utah") &&
            // statesVisited.contains("arizona") &&
            //     statesVisited.contains("newmexico"))
            // {
            //     std::cout << "Awarded 'Visited All 4 Corner States' Achievement!";
            // }
            // int mCount {};
            // for (auto const& state : statesVisited)
            // {
            //     if (state[0] == 'm')
            //     {
            //         ++mCount;
            //     }
            // }
            // if (mCount == 8)
            // {
            //     std::cout << "Awarded 'Visited All M States' Achievement!";
            // }
        }
        else
        {
            // std::cout << "Your score of " << totalScore << " Didn't pass";
        }
    } while (std::next_permutation(innerMatrix.begin(), innerMatrix.end()));
    std::cout << maxScore;
}

std::string Optimizer::returnResultMatrix() const noexcept { return resultMatrix; }

}// namespace alteredstates
