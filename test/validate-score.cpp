// Copyright 2024 Andrew Drogalis
// GNU License
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "state-populations.h"
// inline constexpr int numStates defined in "state-populations"
// inline constexpr std::array<std::pair<std::string_view, int> numStates> statesPopulation defined in
// "state-populations"

constexpr int minThreshold {165'379'868};

int calculateScore() {}

std::string loadJSON()
{
    std::string resultsMatrixStr;
    std::ifstream loadMatrix {"json/result-matrix.json"};
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
    std::vector<char> results;
    std::ifstream loadMatrix {"json/"};

    int const matrixSize = std::sqrt(results.size());

    int totalScore = calculateScore();

    if (totalScore >= minThreshold)
    {
        std::cout << "Congratuations! Your Score of " << totalScore << " Passed!\n";
    }
    else
    {
        std::cout << "Your score of " << totalScore << " Didn't pass";
    }

    return 0;
}
