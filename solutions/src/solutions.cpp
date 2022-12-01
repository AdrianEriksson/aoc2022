#include "../include/solutions.h"

#include <algorithm>
#include <iostream>
#include <vector>

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
}

}  // TestSolution