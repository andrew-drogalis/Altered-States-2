
// Copyright 2024 Andrew Drogalis
// GNU License
#ifndef FIND_LETTER_OCCURRENCES_H
#define FIND_LETTER_OCCURRENCES_H

#include <string>

namespace alteredstates
{

struct LetterOccurrences
{
    LetterOccurrences() = default;

    void findOccurrences();

    [[nodiscard]] std::string returnResultInner() const noexcept;

    [[nodiscard]] std::string returnResultOuter() const noexcept;

    std::string resultMatrixInner;
    std::string resultMatrixOuter;
};

}// namespace alteredstates
#endif
