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

	int sum = 0;
	for (const auto& line : input)
	{
		std::string strNum = "ZZ";
		std::pair<__int64, __int64> positions = { INT64_MAX, INT64_MIN };
		for (const auto& number : numbers)
		{
			auto search = line.cbegin();
			std::string reg = std::format("({0})|([0-9])", number.first);
			std::regex regex(reg);
			for (std::smatch sm; std::regex_search(search, line.cend(), sm, regex);)
			{
				__int64 foundPos = line.find(sm.str());
				if (foundPos < positions.first)
				{
					if(numbers.count(sm.str()))
						strNum[0] = numbers[sm.str()];
					else
						strNum[0] = sm.str()[0];
					positions.first = foundPos;
				}

				foundPos = line.rfind(sm.str());
				if (foundPos > positions.second)
				{
					if (numbers.count(sm.str()))
						strNum[1] = numbers[sm.str()];
					else
						strNum[1] = sm.str()[0];
					positions.second = foundPos;
				}
				search = sm.suffix().first;
			}
		}
		sum += std::stoi(strNum);
	}
	std::cout << sum;
}
