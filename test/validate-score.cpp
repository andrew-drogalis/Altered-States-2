// Copyright 2024 Andrew Drogalis
// GNU License
#include <cassert>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>

#include "state-populations.h"
// inline constexpr int numStates defined in "state-populations"
// inline constexpr std::array<std::pair<std::string_view, int> numStates> statesPopulation defined in
// "state-populations"

constexpr int minThreshold {165'379'868};
std::unordered_set<std::string_view> statesVisited;

int calculateScore(int matrixSize, std::string const& resultsMatrixStr)
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
            for (const auto& [state, population] : statesPopulation)
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

std::string loadJSON()
{
    std::string resultsMatrixStr;
    std::ifstream loadMatrix {"../json/result-matrix.txt"};
    if (loadMatrix.is_open())
    {
        loadMatrix >> resultsMatrixStr;
        if (! loadMatrix.good())
        {
            std::cout << "Error Reading from File";
            return "";
        }
    }
    else
    {
        std::cout << "Error Opening File";
        return "";
    }
    return resultsMatrixStr;
}

int main()
{
    std::string resultsMatrixStr = loadJSON();
    int const matrixSize         = std::sqrt(resultsMatrixStr.length());
    assert(resultsMatrixStr.length() == matrixSize * matrixSize);

    int totalScore = calculateScore(matrixSize, resultsMatrixStr);

    if (totalScore >= minThreshold)
    {
        std::cout << "Congratulations! Your Score of " << totalScore << " Passed!\n";
        // Extra Achievements
        if (totalScore >= 200'000'000)
        {
            std::cout << "Awarded 200 Million Achievement!";
        }
        if (! statesVisited.contains("california"))
        {
            std::cout << "Awarded 'No California' Achievement!";
        }
        if (statesVisited.contains("pennsylvania"))
        {
            std::cout << "Awarded 'Visited Pennsylvania' Achievement!";
        }
        if (statesVisited.size() >= 20)
        {
            std::cout << "Awarded 'Visited 20 States' Achievement!";
        }
        if (statesVisited.contains("colorado") && statesVisited.contains("utah") && statesVisited.contains("arizona") && statesVisited.contains("newmexico"))
        {
            std::cout << "Awarded 'Visited All 4 Corner States' Achievement!"; 
        }
        int mCount {};
        for (const auto& state : statesVisited)
        {
            if (state[0] == 'm')
            {
                ++mCount;
            }
        }
        if (mCount == 8)
        {
            std::cout << "Awarded 'Visited All M States' Achievement!";
        }
    }
    else
    {
        std::cout << "Your score of " << totalScore << " Didn't pass";
    }

    return 0;
}
