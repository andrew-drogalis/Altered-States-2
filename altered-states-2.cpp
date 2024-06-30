// Copyright 2024 Andrew Drogalis
// GNU License
#include <fstream>
#include <iostream>
#include <string>

#include "optimize-matrix.hpp"
#include "states_correlation.hpp"

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

std::string loadFromJson(std::string const& fileName)
{
    std::string resultsStr;
    std::ifstream saveMatrix {fileName};
    if (saveMatrix.is_open())
    {
        saveMatrix >> resultsStr;
        if (! saveMatrix.good())
        {
            std::cout << "Error Reading File";
            return "";
        }
    }
    else
    {
        std::cout << "Error Opening File";
        return "";
    }
    return resultsStr;
}

int main()
{
    alteredstates::StatesCorrelation correlation {};
    correlation.statesLetterCorrelation();
    std::string statesCorrelationStr = correlation.buildStringFromArray();
    std::string fileName             = "json/state-correlation.json";

    if (saveToJSON(statesCorrelationStr, fileName))
    {
        return 1;
    }

    std::string defaultMatrix = loadFromJson("json/default-matrix-iter-4.json");

    alteredstates::Optimizer optimizer(defaultMatrix);
    optimizer.maximizeScore();
    std::string resultsMatrix  = optimizer.returnResultMatrix();
    std::string resultFileName = "result/result-string.txt";

    if (saveToJSON(resultsMatrix, resultFileName))
    {
        return 1;
    }

    return 0;
}
