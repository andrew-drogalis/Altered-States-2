// Copyright 2024 Andrew Drogalis
// GNU License
#ifndef FIND_BEST_RESULT_H
#define FIND_BEST_RESULT_H

#include <string>
#include <unordered_set>

namespace alteredstates
{

struct Optimizer
{
    Optimizer() = default;

    Optimizer(std::string& innerMatrix, std::string& outerMatrix);

    [[nodiscard]] int calculateScore(int matrixSize, std::string const& resultsMatrixStr);

    void maximizeScore();

    [[nodiscard]] std::string returnResultMatrix() const noexcept;

    std::unordered_set<std::string_view> statesVisited;
    std::string innerMatrix;
    std::string outerMatrix;
    std::string resultMatrix;
};

}// namespace alteredstates
#endif
