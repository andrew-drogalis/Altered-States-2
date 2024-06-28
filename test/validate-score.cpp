// Copyright 2024 Andrew Drogalis
// GNU License
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>

#include "state-populations.h"
// inline constexpr int numStates defined in "state-populations"
// inline constexpr std::array<std::pair<std::string_view, int> numStates> statesPopulation defined in
// "state-populations"

constexpr int minThreshold {165'379'868};

std::unordered_map<std::string, double> statesPopulationHashMap;

void setStatesHashMap()
{
    for (auto [state, population] : statesPopulation) { statesPopulationHashMap[std::string {state}] = population; }
}

int calculateScore(int matrixSize, std::string const& resultsMatrixStr)
{
    int totalScore {};
    int const numOfDirections {8};
    std::array<int, numOfDirections + 1> directions = {1, 0, -1, 0, 1, 1, -1, -1, 1};

    std::function<void(int, int, int, int)> searchMatrix = [&](int index, int row, int col, int iter) {
        for (int i {}; i < numOfDirections; ++i)
        {
            int nextRow = row + directions[i];
            int nextCol = col + directions[i + 1];
             std::cout << nextRow << nextCol << iter << '\n';
            if (nextRow >= 0 && nextCol >= 0 && nextRow < matrixSize && nextCol < matrixSize)
            {
                int index = matrixSize * nextRow + nextCol;
                searchMatrix(index, nextRow, nextCol, iter + 1);
            }
        }
    };

    for (int row {}; row < matrixSize; ++row)
    {
        for (int col {}; col < matrixSize; ++col)
        {
            int index = matrixSize * row + col;
            std::cout << row << col << index << '\n';
            searchMatrix(index, row, col, 1);
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
    setStatesHashMap();

    int totalScore = calculateScore(matrixSize, resultsMatrixStr);

    if (totalScore >= minThreshold)
    {
        std::cout << "Congratulations! Your Score of " << totalScore << " Passed!\n";
        if (totalScore >= 200'000'000)
        {
            std::cout << "Awarded 200 Million Achievement!";
        }
        if (statesPopulationHashMap["california"])
        {
            std::cout << "Awarded 'No California' Achievement!";
        }
        if (! statesPopulationHashMap["pennsylvania"])
        {
            std::cout << "Awarded 'Visited Pennsylvania' Achievement!";
        }
        // - 20S: visits at least 20 states
        // - M8: contains all 8 states that begin with an M
        // - 4C: contains the “Four Corners” states
    }
    else
    {
        std::cout << "Your score of " << totalScore << " Didn't pass";
    }

    return 0;
}
