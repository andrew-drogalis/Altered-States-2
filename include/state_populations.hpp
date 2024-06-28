// Copyright 2024 Andrew Drogalis
// GNU License
#ifndef STATE_POPULATION_H
#define STATE_POPULATION_H

#include <array>
#include <string_view>

namespace alteredstates
{

inline constexpr int numStates {50};

using namespace std::literals::string_view_literals;
// Compile time array with states and population as of 2020 census
inline constexpr std::array<std::pair<std::string_view, int>, numStates> statesPopulation {{
    {"alabama"sv, 5'024'279},
    {"alaska"sv, 733'391},
    {"arizona"sv, 7'151'502},
    {"arkansas"sv, 3'011'524},
    {"california"sv, 39'538'223},
    {"colorado"sv, 5'773'714},
    {"connecticut"sv, 3'605'944},
    {"delaware"sv, 989'948},
    {"florida"sv, 21'538'187},
    {"georgia"sv, 10'711'908},
    {"hawaii"sv, 1'455'271},
    {"idaho"sv, 1'839'106},
    {"illinois"sv, 12'812'508},
    {"indiana"sv, 6'785'528},
    {"iowa"sv, 3'190'369},
    {"kansas"sv, 2'937'880},
    {"kentucky"sv, 4'505'836},
    {"louisiana"sv, 4'657'757},
    {"maine"sv, 1'362'359},
    {"maryland"sv, 6'177'224},
    {"massachusetts"sv, 7'029'917},
    {"michigan"sv, 10'077'331},
    {"minnesota"sv, 5'706'494},
    {"mississippi"sv, 2'961'279},
    {"missouri"sv, 6'154'913},
    {"montana"sv, 1'084'225},
    {"nebraska"sv, 1'961'504},
    {"nevada"sv, 3'104'614},
    {"newhampshire"sv, 1'377'529},
    {"newjersey"sv, 9'288'994},
    {"newmexico"sv, 2'117'522},
    {"newyork"sv, 20'201'249},
    {"northcarolina"sv, 10'439'388},
    {"northdakota"sv, 779'094},
    {"ohio"sv, 11'799'448},
    {"oklahoma"sv, 3'959'353},
    {"oregon"sv, 4'237'256},
    {"pennsylvania"sv, 13'002'700},
    {"rhodeisland"sv, 1'097'379},
    {"southcarolina"sv, 5'118'425},
    {"southdakota"sv, 886'667},
    {"tennessee"sv, 6'910'840},
    {"texas"sv, 29'145'505},
    {"utah"sv, 3'271'616},
    {"vermont"sv, 643'077},
    {"virginia"sv, 8'631'393},
    {"washington"sv, 7'705'281},
    {"westvirginia"sv, 1'793'716},
    {"wisconsin"sv, 5'893'718},
    {"wyoming"sv, 576'851},
}};

}// namespace alteredstates
#endif
