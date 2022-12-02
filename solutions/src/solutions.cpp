#include "../include/solutions.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

namespace Solutions
{
namespace DayOne
{
void partOne(std::vector<std::string> input)
{
    int currentMax{0}, tempSum{0};
    for (std::string& elem : input)
    {
        if (elem.empty())
        {
            if (tempSum > currentMax)
            {
                currentMax = tempSum;
            }
            tempSum = 0;
            continue;
        }
        tempSum += std::stoi(elem);
    }
    std::cout << "Day 1, part 1: " << currentMax << std::endl;
}

void partTwo(std::vector<std::string> input)
{
    int tempSum{0};
    std::vector<int> calorieVec;
    for (std::string& elem : input)
    {
        if (elem.empty())
        {
            calorieVec.emplace_back(tempSum);
            tempSum = 0;
            continue;
        }
        tempSum += std::stoi(elem);
    }

    std::sort(calorieVec.begin(), calorieVec.end(), std::greater<int>());
    int topThree{0};
    std::for_each_n(calorieVec.begin(), 3, [&](int elem) { topThree += elem; });

    std::cout << "Day 1, part 2: " << topThree << std::endl;
}
}  // DayOne

namespace DayTwo
{
std::map<char, int> scoreMap{{'X', 1}, {'Y', 2}, {'Z', 3}};
std::map<char, char> winMap{{'A', 'Y'}, {'B', 'Z'}, {'C', 'X'}};
std::map<char, char> drawMap{{'A', 'X'}, {'B', 'Y'}, {'C', 'Z'}};
std::map<char, char> loseMap{{'A', 'Z'}, {'B', 'X'}, {'C', 'Y'}};

void partOne(std::vector<std::vector<char>> input)
{
    int score{0};
    for (std::vector<char> match : input)
    {
        score += scoreMap[match[1]];
        if (winMap[match[0]] == match[1])
        {
            score += 6;
        }
        else if (drawMap[match[0]] == match[1])
        {
            score += 3;
        }
    }
    std::cout << "Day 2, part 1: " << score << std::endl;
}


void partTwo(std::vector<std::vector<char>> input)
{
    int score{0};
    for (std::vector<char> match : input)
    {
        switch (match[1])
        {
        case 'X':
            score += scoreMap[loseMap[match[0]]];
            break;
        case 'Y':
            score += scoreMap[drawMap[match[0]]];
            score += 3;
            break;
        case 'Z':
            score += scoreMap[winMap[match[0]]];
            score += 6;
            break;
        default:
            break;
        }
    }
    std::cout << "Day 2, part 2: " << score << std::endl;
}
}
}  // TestSolution
