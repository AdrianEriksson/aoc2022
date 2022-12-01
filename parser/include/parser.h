#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

namespace 
{
std::string pathToFile(std::string name)
{
    return "../input/" + name;
}
}

namespace Parser
{
template <typename T>
void fillVec(std::string name, std::vector<T>& vec)
{
    std::string path{pathToFile(name)};
    std::ifstream inputFile;
    inputFile.open(path, std::ifstream::in);
    if (!inputFile.is_open())
    {
        std::cout << "Unable to open file..." << std::endl;
        exit(1);
    }

    std::string line;
    while (std::getline(inputFile, line))
    {
        if (line.empty())
        {
            vec.push_back(T());
            continue;
        }
        vec.push_back(static_cast<T>(line));
    }
    inputFile.close();
};

template <typename T>
void fillMatrix(std::string name, std::vector<std::vector<T>>& mat)
{
    std::string path{pathToFile(name)};
    std::ifstream inputFile;
    inputFile.open(path.c_str(), std::ifstream::in);
    if (!inputFile.is_open())
    {
        std::cout << "Unable to open file..." << std::endl;
    }

    std::string line;
    while (std::getline(inputFile, line, '\n'))
    {
        std::vector<T> row;
        std::stringstream ss(line);

        T elem;
        while (ss >> elem)
        {
            row.push_back(elem);
        }
        mat.push_back(row);
    }
    inputFile.close();
}
}  // Parser
