#include "../include/solutions.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <string_view>
#include <stack>

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
}  // DayTwo

namespace DayThree
{
int getScore(char ch)
{
    const int chVal{static_cast<int>(ch)};
    if (std::isupper(chVal))
    {
        return chVal - 38;
    }
    return chVal - 96;
}

void partOne(std::vector<std::string> input)
{
    int score {0};
    for (std::string& elem : input)
    {
        std::string first{elem.substr(0, elem.size() / 2)};
        std::string second{elem.substr(elem.size() / 2, elem.size())};

        std::sort(first.begin(), first.end());
        std::sort(second.begin(), second.end());

        std::vector<char> intersection;
        std::set_intersection(first.begin(), first.end(), second.begin(), second.end(),
                              std::back_inserter(intersection));

        score += getScore(intersection[0]);
    }
    std::cout << "Day 3, part 1: " << score << std::endl;
}

void partTwo(std::vector<std::string> input)
{
    int score {0};
    for (uint16_t i = 0; i < input.size(); i += 3)
    {
        std::string first{input[i]};
        std::string second{input[i + 1]};
        std::string third{input[i + 2]};

        std::sort(first.begin(), first.end());
        std::sort(second.begin(), second.end());
        std::sort(third.begin(), third.end());

        std::string firstIntersection;
        std::set_intersection(first.begin(), first.end(), second.begin(), second.end(),
                              std::back_inserter(firstIntersection));
        
        std::sort(firstIntersection.begin(), firstIntersection.end());

        std::string secondIntersection;
        std::set_intersection(firstIntersection.begin(), firstIntersection.end(), third.begin(), third.end(),
                              std::back_inserter(secondIntersection));
        
        score += getScore(secondIntersection[0]);
    }
    std::cout << "Day 3, part 2: " << score << std::endl;
}
}  // DayThree

namespace DayFour
{
struct Assignments
{
    Assignments(int lb, int up) : lowerBound(lb), upperBound(up) {};
    int lowerBound;
    int upperBound;

    bool operator<(Assignments other)
    {
        return (lowerBound >= other.lowerBound) && (upperBound <= other.upperBound);
    }

    bool overlaps(Assignments other)
    { 
        return (upperBound >= other.lowerBound && lowerBound <= other.upperBound);
    }
};

std::pair<Assignments, Assignments> extractAssignmentPair(std::string pair)
{
    std::istringstream ssPair(pair);
    std::string assignee;
    std::vector<int> sections;
    while (std::getline(ssPair, assignee, ','))
    {
        std::istringstream ssAssignee(assignee);
        std::string section;
        while (std::getline(ssAssignee, section, '-'))
        {
            sections.push_back(std::stoi(section));
        }
    }
    return std::make_pair<Assignments, Assignments>(Assignments(sections[0], sections[1]), Assignments(sections[2], sections[3]));
}

void partOne(std::vector<std::string> input)
{
    int score{0};
    for (std::string pair : input)
    {
        auto assignmentPair{extractAssignmentPair(pair)};
        if (assignmentPair.first < assignmentPair.second || assignmentPair.second < assignmentPair.first)
        {
            score++;
        }
    }
    std::cout << "Day 4, part 1: " << score << std::endl;
}

void partTwo(std::vector<std::string> input)
{
    int score{0};
    for (std::string pair : input)
    {
        auto assignmentPair{extractAssignmentPair(pair)};
        if (assignmentPair.second.overlaps(assignmentPair.first))
        {
            score++;
        }
    }
    std::cout << "Day 4, part 2: " << score << std::endl;
}
}  // DayFour

namespace DayFive
{
int getDepthOfStacks(std::vector<std::string>& input)
{
    auto result{std::find_if(input.begin(), input.end(), [](std::string &row)
                             { return row.starts_with(std::string_view(" 1 ")); })};

    if (result != input.end())
    {
        return std::distance(input.begin(), result);
    }
    return 0;
}

int getNumberOfStacks(std::vector<std::string>& input, int stackDepth)
{
    return input[stackDepth].at(input[stackDepth].size() - 2) - '0';
}

std::vector<std::stack<char>> getStacks(std::vector<std::string>& input)
{
    const int depth{getDepthOfStacks(input)};
    const int entities{getNumberOfStacks(input, depth)};
    std::vector<std::stack<char>> stacks(entities);
    std::for_each_n(input.rend() - depth, depth, [&](std::string& row)
    {
        for (uint16_t i = 0; i < entities; i++)
        {
            if (char candidate = row[1 + i*4]; candidate != ' ')
            {
                stacks[i].push(candidate);
            }
        }
    });
    return stacks;
}

std::vector<std::vector<char>> getStacksAsVectors(std::vector<std::string>& input)
{
    const int depth{getDepthOfStacks(input)};
    const int entities{getNumberOfStacks(input, depth)};
    std::vector<std::vector<char>> stacks(entities);
    std::for_each_n(input.rend() - depth, depth, [&](std::string& row)
    {
        for (uint16_t i = 0; i < entities; i++)
        {
            if (char candidate = row[1 + i*4]; candidate != ' ')
            {
                stacks[i].push_back(candidate);
            }
        }
    });
    return stacks;
}

std::vector<std::string> getInstruction(std::string inputLine)
{
    std::istringstream ssInputLine(inputLine);
    std::string input;
    std::vector<std::string> inputs;
    while (std::getline(ssInputLine, input, ' '))
    {
        inputs.push_back(input);
    }
    return inputs;
}

void partOne(std::vector<std::string> input)
{
    const int instructionStart{getDepthOfStacks(input) + 2};
    std::vector<std::stack<char>> stacks{getStacks(input)};
    std::for_each(input.begin() + instructionStart, input.end(), [&](std::string &inputLine)
                  {
                    std::vector<std::string> inputs{getInstruction(inputLine)};
                    const int move{std::stoi(inputs[1])};
                    const int source{std::stoi(inputs[3]) - 1};
                    const int target{std::stoi(inputs[5]) - 1};

                    for (int i = 0; i < move; i++)
                    {
                        stacks[target].push(stacks[source].top());
                        stacks[source].pop();
                    } });

    std::string result;
    for (std::stack<char> stack : stacks)
    {
        result += stack.top();
    }
    std::cout << "Day 5, part 1: " << result << std::endl;
}

void partTwo(std::vector<std::string> input)
{
    const int instructionStart{getDepthOfStacks(input) + 2};
    std::vector<std::vector<char>> stacks{getStacksAsVectors(input)};

    std::for_each(input.begin() + instructionStart, input.end(), [&](std::string &inputLine)
                  {
                    std::vector<std::string> inputs{getInstruction(inputLine)};
                    const int move{std::stoi(inputs[1])};
                    const int source{std::stoi(inputs[3]) - 1};
                    const int target{std::stoi(inputs[5]) - 1};
                    stacks[target].insert(stacks[target].end(), 
                        std::make_move_iterator(stacks[source].end() - move),
                        std::make_move_iterator(stacks[source].end()));
                    stacks[source].erase(stacks[source].end() - move, stacks[source].end()); });

    std::string result;
    for (std::vector<char> stack : stacks)
    {
        result += stack.back();
    }

    std::cout << "Day 5, part 2: " << result << std::endl;
}
}  // DayFive
}  // TestSolution
