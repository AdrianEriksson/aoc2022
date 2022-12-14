#include "include/parser.h"
#include "include/solutions.h"

#include <iostream>

template <typename T>
std::ostream& operator << (std::ostream& os, std::vector<T>& vec)
{
	for (auto& elem : vec)
	{
		os << elem << std::endl;
	}
	return os;
}

template <typename T>
std::ostream& operator << (std::ostream& os, std::vector<std::vector<T>>& mat)
{
	for (std::vector<T> row : mat)
	{
		for (T& elem : row)
		{
			os << elem << ' ';
		}
		os << std::endl;
	}
	return os;
}

int main()
{
	std::vector<std::vector<char>> input;
	Parser::fillMatrix("day12_partOne.txt", input);
	Solutions::DayTwelve::partOne(input);
	Solutions::DayTwelve::partTwo(input);
}