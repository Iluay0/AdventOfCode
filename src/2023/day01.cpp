#include "days.h"

void aoc::y2023::day01_part1()
{
	int sum = 0;
	for (const auto& line : aoc::GetInputData())
	{
		std::regex regex("([0-9])");
		std::smatch smFirst;
		std::match_results<std::string::const_reverse_iterator> smLast;
		if (std::regex_search(line, smFirst, regex) && std::regex_search(line.crbegin(), line.crend(), smLast, regex))
		{
			std::string strNum = smFirst.str() + smLast.str();
			sum += std::stoi(strNum);
		}
	}
	std::cout << sum << std::endl;
}

void aoc::y2023::day01_part2()
{
	std::map<std::string, char> numbersReverse;
	std::map<std::string, char> numbers {
		{ "one", '1' },
		{ "two", '2' },
		{ "three", '3' },
		{ "four", '4' },
		{ "five", '5' },
		{ "six", '6' },
		{ "seven", '7' },
		{ "eight", '8' },
		{ "nine", '9' },
	};

	std::string searchString = "";
	std::string searchStringRev = "";
	for (const auto& [key, value] : numbers)
	{
		std::string keyRev{ key.rbegin(), key.rend() };
		numbersReverse.insert({ keyRev, value });

		searchString += std::format("({0})|", key);
		searchStringRev += std::format("({0})|", keyRev);
	}
	searchString += "([0-9])";
	searchStringRev += "([0-9])";

	std::regex regex(searchString);
	std::regex regexRev(searchStringRev);

	int sum = 0;
	for (const auto& line : aoc::GetInputData())
	{
		std::string reverseLine{ line.rbegin(), line.rend() };

		std::smatch smFirst;
		std::smatch smLast;
		if (std::regex_search(line, smFirst, regex) && std::regex_search(reverseLine, smLast, regexRev))
		{
			char chFirst = smFirst.str()[0];
			if (!std::isdigit(chFirst))
				chFirst = numbers[smFirst.str()];

			char chSecond = smLast.str()[0];
			if (!std::isdigit(chSecond))
				chSecond = numbersReverse[smLast.str()];

			sum += std::stoi(std::string{ chFirst, chSecond });
		}
	}
	std::cout << sum << std::endl;
}
