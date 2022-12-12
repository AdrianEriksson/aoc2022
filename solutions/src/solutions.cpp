#include "../include/solutions.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <string_view>
#include <stack>
#include <list>
#include <optional>
#include <memory>

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

namespace DaySix
{
bool hasDuplicate(std::list<char> candidate, int uniques)
{
    candidate.sort();
    candidate.unique();

    if (candidate.size() < uniques)
    {
        return true;
    } 
    return false;
}

void partOne(std::string input)
{
    int position{0};
    std::list<char> candidateMarker{};
    for (int i = 3; i < input.size(); i++)
    {
        if (candidateMarker.empty())
        {
            candidateMarker.insert(candidateMarker.end(), input.begin(), input.begin() + 4);
        }
        else
        {
            candidateMarker.pop_front();
            candidateMarker.push_back(input[i]);
        }

        if (!hasDuplicate(candidateMarker, 4))
        {
            position = i;
            break;
        }
    }
    std::cout << "Day 6, part 1: " << ++position << std::endl;
}

void partTwo(std::string input)
{
    int position{0};
    std::list<char> candidateMarker{};
    for (int i = 13; i < input.size(); i++)
    {
        if (candidateMarker.empty())
        {
            candidateMarker.insert(candidateMarker.end(), input.begin(), input.begin() + 14);
        }
        else
        {
            candidateMarker.pop_front();
            candidateMarker.push_back(input[i]);
        }

        if (!hasDuplicate(candidateMarker, 14))
        {
            position = i;
            break;
        }
    }
    std::cout << "Day 6, part 2: " << ++position << std::endl;
}
}  // DaySix

namespace DaySeven
{
struct File
{
    explicit File(std::string name, uint64_t size) : name_(name), size_(size) {}

    const std::string name_;
    const uint64_t size_;
};

struct DirectoryNode
{
    DirectoryNode(std::string name, std::shared_ptr<DirectoryNode> parent) : name_(name), parent_(parent) {}

    void addFile(std::string name, uint64_t size) { files_.emplace_back(name, size); }
    void addChild(std::shared_ptr<DirectoryNode> child) { children_.push_back(child); } 

    std::vector<std::shared_ptr<DirectoryNode>> children_;
    std::shared_ptr<DirectoryNode> parent_;
    std::vector<File> files_;
    const std::string name_;
    uint64_t size_{0};
};

std::vector<std::string> getInstruction(std::string inputLine)
{
    std::istringstream ssInputLine(inputLine);
    std::string input;
    std::vector<std::string> inputs;
    while (std::getline(ssInputLine, input, ' '))
    {
        inputs.emplace_back(input);
    }
    return inputs;
}

std::shared_ptr<DirectoryNode> populateDirectoryTree(std::vector<std::string>& input)
{
    std::shared_ptr<DirectoryNode> currentDir{std::make_shared<DirectoryNode>("root", nullptr)};
    for (std::string line : input)
    {
        std::vector<std::string> command(getInstruction(line));
        if (command[0] == "$")
        {
            if (command[1] == "cd")
            {
                if (command[2] == "..")
                {
                    currentDir = currentDir->parent_;
                }
                else
                {   
                    std::shared_ptr<DirectoryNode> newDir{std::make_shared<DirectoryNode>(command[2], currentDir)};
                    currentDir->addChild(newDir);
                    currentDir = newDir;
                }
            }
            else if (command[1] == "ls")
            {
                continue;
            }
        }
        else if (command[0] == "dir")
        {
            continue;
        }
        else
        {
            currentDir->addFile(command[1], std::stoll(command[0]));
        }
    }

    while(currentDir.get()->name_ != "root")
    {
        currentDir = currentDir->parent_;
    }
    return currentDir;
}

uint64_t traverseTreeAndSetSize(std::shared_ptr<DirectoryNode> node)
{
    uint64_t size{0};
    for (File file : node.get()->files_)
    {
        size += file.size_;
    }
    node.get()->size_ = size;

    if (node.get()->children_.empty())
    {
        return node.get()->size_ ;
    }

    for (auto child : node.get()->children_)
    {
        node.get()->size_ += traverseTreeAndSetSize(child);
    }
    return node.get()->size_;
}

void traverseTreePartOne(std::shared_ptr<DirectoryNode> node, uint64_t& result)
{
    if (node.get()->size_ <= 100000)
    {
        result += node.get()->size_;
    }

    for (auto child : node.get()->children_)
    {
        traverseTreePartOne(child, result);
    }
    return;
}

void traverseTreePartTwo(std::shared_ptr<DirectoryNode> node, std::vector<long long> &candidates, uint64_t threshold)
{
    if (node.get()->size_ >= threshold)
    {
        candidates.push_back(node.get()->size_);
    }

    for (auto child : node.get()->children_)
    {
        traverseTreePartTwo(child, candidates, threshold);
    }
    return;
}

void partOne(std::vector<std::string> input)
{
    std::shared_ptr<DirectoryNode> root{populateDirectoryTree(input)};
    traverseTreeAndSetSize(root);
    uint64_t result{0};
    traverseTreePartOne(root, result);
    std::cout << "Day 7, part 1: " << result << std::endl;
}

void partTwo(std::vector<std::string> input)
{
    std::shared_ptr<DirectoryNode> root{populateDirectoryTree(input)};
    traverseTreeAndSetSize(root);
    
    std::vector<long long> candidateDirs;
    traverseTreePartTwo(root, candidateDirs, root.get()->size_ - 40000000);
    std::sort(candidateDirs.begin(), candidateDirs.end());
    
    std::cout << "Day 7, part 2: " << candidateDirs[0] << std::endl;
}
}  // DaySeven

namespace DayEight
{
bool isVisible(std::pair<int, int> coordinate, std::vector<std::vector<char>>& input)
{
    std::array<bool, 4> exposedSides{true, true, true, true};
    for (int i = coordinate.second - 1; i >= 0; --i)
    {
        if (input[coordinate.first][i] >= input[coordinate.first][coordinate.second])
        {
            exposedSides[0] = false;
            break;
        }
    }

    const std::size_t width{input[0].size()};
    for (int i = coordinate.second + 1; i < width; i++)
    {
        if (input[coordinate.first][i] >= input[coordinate.first][coordinate.second])
        {
            exposedSides[1] = false;
            break;
        }
    }

    for (int i = coordinate.first - 1; i >= 0; i--)
    {
        if (input[i][coordinate.second] >= input[coordinate.first][coordinate.second])
        {
            exposedSides[2] = false;
            break;
        }
    }

    const std::size_t height{input.size()};
    for (int i = coordinate.first + 1; i < height; i++)
    {
        if (input[i][coordinate.second] >= input[coordinate.first][coordinate.second])
        {
            exposedSides[3] = false;
            break;
        }
    }

    bool isVisible{false};
    std::for_each(exposedSides.begin(), exposedSides.end(), [&](const bool side) { if (side) { isVisible = true; } });
    return isVisible;
}

int getScenicScore(std::pair<int, int> coordinate, std::vector<std::vector<char>>& input)
{
    std::array<int, 4> scenicDistances{0, 0, 0, 0};
    for (int i = coordinate.second - 1; i >= 0; --i)
    {
        scenicDistances[0]++;
        if (input[coordinate.first][i] >= input[coordinate.first][coordinate.second])
        {
            break;
        }
    }

    const std::size_t width{input[0].size()};
    for (int i = coordinate.second + 1; i < width; i++)
    {
        scenicDistances[1]++;
        if (input[coordinate.first][i] >= input[coordinate.first][coordinate.second])
        {
            break;
        }
    }

    for (int i = coordinate.first - 1; i >= 0; i--)
    {
        scenicDistances[2]++;
        if (input[i][coordinate.second] >= input[coordinate.first][coordinate.second])
        {
            break;
        }
    }
    
    const std::size_t height{input.size()};
    for (int i = coordinate.first + 1; i < height; i++)
    {
        scenicDistances[3]++;
        if (input[i][coordinate.second] >= input[coordinate.first][coordinate.second])
        {
            break;
        }
    }
    
    return scenicDistances[0] * scenicDistances[1] * scenicDistances[2] * scenicDistances[3];
}

void partOne(std::vector<std::vector<char>> input)
{
    std::vector<std::pair<int, int>> visibles;
    const std::size_t width{input[0].size()};
    const std::size_t height{input.size()};
    const std::size_t edges{2 * width + 2 * height - 4};

    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            std::pair<int, int> coordinate{std::make_pair(i, j)};
            if (isVisible(coordinate, input))
            {
                visibles.push_back(coordinate);
            }
        }
    }

    std::cout << "Day 7, part 1: " << visibles.size() + edges << std::endl;
}

void partTwo(std::vector<std::vector<char>> input)
{
    std::vector<int> scenicScores;
    const std::size_t width{input[0].size()};
    const std::size_t height{input.size()};
    const std::size_t edges{2 * width + 2 * height - 4};

    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            std::pair<int, int> coordinate{std::make_pair(i, j)};
            scenicScores.emplace_back(getScenicScore(coordinate, input));
        }
    }
    std::sort(scenicScores.begin(), scenicScores.end(), std::greater<int>());

    std::cout << "Day 7, part 2: " << scenicScores[0] << std::endl;
}
}  // DayEight

namespace DayEleven
{
enum OperationType
{
    Addtion,
    Multiplication,
    Square
};

struct Operation
{
    explicit Operation(OperationType type, uint8_t val) : type_(type), val_(val) {}
    uint64_t operate(uint64_t item) const
    {
        switch (type_)
        {
        case OperationType::Addtion:
            return item + val_;
            break;
        case OperationType::Multiplication:
            return item * val_;
        case OperationType::Square:
            return item*item;
        }
    }
    std::string toString() const
    {
        switch (type_)
        {
        case OperationType::Addtion:
            return "+ " + std::to_string(val_);
            break;
        case OperationType::Multiplication:
            return "* " + std::to_string(val_);
        case OperationType::Square:
            return "* old";
        }
    }
    const OperationType type_;
    const uint8_t val_;
};

struct Monkey
{
    explicit Monkey(uint8_t id, std::list<uint64_t> items, Operation operation, uint8_t testVal, std::pair<uint8_t, uint8_t> partners) 
        : id_(id), items_(items), operation_(operation), testVal_(testVal), partners_(partners){};

    void addItem(uint64_t item) { items_.emplace_back(item); }
    void popItem() { items_.pop_front(); }
    uint64_t getItem() const { return items_.front(); }
    void doOperation() 
    { 
        inspections_++;
        items_.front() = operation_.operate(items_.front()); 
    }
    void doReduction() { items_.front() /= 3; }
    uint8_t doTest()
    { 
        if (items_.front() % testVal_ == 0)
        {
            return std::get<0>(partners_);
        }
        return std::get<1>(partners_);
    }
    
    const uint8_t id_;
    uint64_t inspections_{0};
    std::list<uint64_t> items_{};
    const Operation operation_;
    const uint8_t testVal_;
    const std::pair<uint8_t, uint8_t> partners_;
};

std::ostream& operator << (std::ostream& os, const Monkey& monkey)
{
    os << "Monkey " << std::to_string(monkey.id_) << ":\n"
        << "Starting items: ";
    for (uint64_t item : monkey.items_)
    {
        os << std::to_string(item) << " ";
    }
    os << "\nOperation: new = old " << monkey.operation_.toString() << "\n"
        << "Test: divisible by " << std::to_string(monkey.testVal_) << "\n"
        << "\tIf true: throw to monkey " << std::to_string(std::get<0>(monkey.partners_)) << "\n"
        << "\tIf true: throw to monkey " << std::to_string(std::get<1>(monkey.partners_)) << "\n"
        << "Inspections: " << std::to_string(monkey.inspections_) << "\n";
    return os;
}

std::vector<Monkey> getMonkeys(std::vector<std::vector<std::string>> input)
{
    std::vector<Monkey> monkeys;

    uint8_t id;
    std::list<uint64_t> items;
    OperationType operationType;
    uint8_t operationVal{0};
    uint8_t testVal;
    uint8_t partnerTrue{0};
    uint8_t partnerFalse{0};
    for (uint8_t i = 0; i < input.size(); i++)
    {
        if (input[i].empty())
        {
            monkeys.emplace_back(id, items, Operation(operationType, operationVal), testVal, std::make_pair(partnerTrue, partnerFalse));
            items.clear();
        }
        else if (input[i][0] == "Monkey")
        {
            std::string idStr(input[i][1]);
            id = std::stoi(idStr.substr(0, idStr.size()-1));
        }
        else if (input[i][0] == "Starting")
        {
            std::for_each(input[i].begin() + 2, input[i].end(),
                    [&] (std::string itemStr) 
                        {
                            if (itemStr.ends_with(','))
                            {
                                items.emplace_back(std::stoi(itemStr.substr(0, itemStr.size()-1)));
                                return;
                            }
                            items.emplace_back(std::stoi(itemStr));
                            return;
                        });
        }
        else if (input[i][0] == "Operation:")
        {
            if (input[i][4] == "+")
            {
                operationType = OperationType::Addtion;
                operationVal  = std::stoi(input[i][5]);
            }
            else if (input[i][5] == "old")
            {
                operationType = OperationType::Square;
                operationVal  = 0;
            }
            else
            {
                operationType = OperationType::Multiplication;
                operationVal  = std::stoi(input[i][5]);
            }
        }
        else if (input[i][0] == "Test:")
        {
            testVal = std::stoi(input[i][3]);
        }
        else if (input[i][0] == "If" && input[i][1] == "true:")
        {
            partnerTrue = std::stoi(input[i][5]);
        }
        else if (input[i][0] == "If" && input[i][1] == "false:")
        {
            partnerFalse = std::stoi(input[i][5]);
        }
    }
    return monkeys;
}

void partOne(std::vector<std::vector<std::string>> input)
{
    std::vector<Monkey> monkeys{getMonkeys(input)};
    uint8_t rounds{20};
    for (uint8_t i = 0; i < rounds; i++)
    {
        for (Monkey& monkey : monkeys)
        {
            uint8_t size = monkey.items_.size();
            for (uint8_t j = 0; j < size; j++)
            {
                monkey.doOperation();
                monkey.doReduction();
                monkeys[monkey.doTest()].addItem(monkey.getItem());
                monkey.popItem();
            }
        }
    }
    
    std::vector<uint64_t> inspections;
    for (auto& monkey : monkeys)
    {
        inspections.emplace_back(monkey.inspections_);
    }
    std::sort(inspections.begin(), inspections.end(), std::greater<uint64_t>());
    std::cout << "Day 7, part 1: " << inspections[0]*inspections[1] << std::endl;
}
void partTwo(std::vector<std::vector<std::string>> input)
{
    std::vector<Monkey> monkeys{getMonkeys(input)};
    uint16_t rounds{10000};
    
    uint32_t lcm = 1;
    for (auto& monkey : monkeys)
    {
        lcm *= monkey.testVal_;
    }

    for (uint16_t i = 0; i < rounds; i++)
    {
        for (Monkey& monkey : monkeys)
        {
            uint16_t size = monkey.items_.size();
            for (uint16_t j = 0; j < size; j++)
            {
                monkey.doOperation();
                monkeys[monkey.doTest()].addItem(monkey.getItem() % lcm);
                monkey.popItem();
            }
        }
    }
    
    std::vector<uint64_t> inspections;
    for (auto& monkey : monkeys)
    {
        inspections.emplace_back(monkey.inspections_);
    }
    std::sort(inspections.begin(), inspections.end(), std::greater<uint64_t>());

    uint64_t score{inspections[0]*inspections[1]};
    std::cout << "Day 7, part 2: " << score << std::endl;
}
}  // DayEleven
}  // Solutions
