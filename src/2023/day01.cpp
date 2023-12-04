#include "days.h"

static constexpr uint16_t year = 2023;
static constexpr uint8_t day = 1;

void aoc::y2023::day01_part1()
{
	auto input = aoc::ParseInputFile<std::deque<std::string>>(aoc::GetInputPath(year, day));

	int sum = 0;
	for (const auto& line : input)
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
	std::cout << sum;
}

void aoc::y2023::day01_part2()
{
	auto input = aoc::ParseInputFile<std::deque<std::string>>(aoc::GetInputPath(year, day));

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

	std::string searchString;
	for (const auto& it : numbers)
	{
		searchString += std::format("({0})|", it.first);
	}
	searchString += "([0-9])";
	std::regex regex(searchString);

	int sum = 0;
	for (const auto& line : input)
	{
		std::string strNum = "ZZ";
		std::pair<__int64, __int64> positions = { INT64_MAX, INT64_MIN };

		auto search = line.cbegin();
		for (std::smatch sm; std::regex_search(search, line.cend(), sm, regex);)
		{
			char chNum = sm.str()[0];
			if (!std::isdigit(chNum))
				chNum = numbers[sm.str()];

			__int64 foundPos = line.find(sm.str());
			if (foundPos < positions.first)
			{
				strNum[0] = chNum;
				positions.first = foundPos;
			}

			foundPos = line.rfind(sm.str());
			if (foundPos > positions.second)
			{
				strNum[1] = chNum;
				positions.second = foundPos;
			}

			search = sm.suffix().first;
			if(sm.str().length() != 1)
				search--;
		}

		sum += std::stoi(strNum);
	}
	std::cout << sum;
}
