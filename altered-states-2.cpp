// Copyright 2024 Andrew Drogalis
// GNU License
#include <fstream>
#include <iostream>
#include <string>

#include "find_best_result.hpp"
#include "find_letter_occurrences.hpp"

int saveToJSON(std::string const& resultsMatrixStr, std::string const& fileName)
{
    // Save results to file for export to Jane Street for judging
    std::ofstream saveMatrix {fileName};
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
    alteredstates::LetterOccurrences letter;
    letter.findOccurrences();
    std::string innerMatrix = letter.returnResultInner();
    std::string outerMatrix = letter.returnResultOuter();

    alteredstates::Optimizer optimize(innerMatrix, outerMatrix);
    optimize.maximizeScore();
    std::string resultsMatrix = optimize.returnResultMatrix();

    std::string innerResultFile = "result/result-string.txt";

    return saveToJSON(resultsMatrix, innerResultFile);
}
