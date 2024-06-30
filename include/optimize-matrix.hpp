// Copyright 2024 Andrew Drogalis
// GNU License
#ifndef OPTIMIZE_MATRIX_H
#define OPTIMIZE_MATRIX_H

#include <string>
#include <unordered_set>

namespace alteredstates
{

struct Optimizer
{
    Optimizer() = default;

    explicit Optimizer(std::string& defaultMatrix);

    [[nodiscard]] int calculateScore(int matrixSize, std::string const& resultsMatrixStr);

    void maximizeScore();

    [[nodiscard]] std::string returnResultMatrix() const noexcept;

    std::unordered_set<std::string_view> statesVisited;
    std::string defaultMatrix;
    std::string resultMatrix;
};

}// namespace alteredstates
#endif
