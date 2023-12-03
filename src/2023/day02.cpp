#include "days.h"

static constexpr uint16_t year = 2023;
static constexpr uint8_t day = 2;

void aoc::y2023::day02_part1()
{
	auto input = aoc::ParseInputFile<std::deque<std::string>>(aoc::GetInputPath(year, day));

	std::regex regex("(?:\\s?(\\d+) (\\w+),?;?)");
	std::regex regexGame("Game (\\d+)");

	std::map<std::string, int32_t> maxAllowed{
		{ "red", 12 },
		{ "green", 13 },
		{ "blue", 14 }
	};

	int sum = 0;
	for (const auto& line : input)
	{
		auto split = aoc::SplitString<std::deque<std::string>>(line, ": ");
		bool isPossible = true;
		int32_t lastNumShown = 0;
		auto search = split[1].cbegin();
		for (std::smatch sm; std::regex_search(search, split[1].cend(), sm, regex);)
		{
			if (std::stoi(sm[1].str()) > maxAllowed[sm[2].str()])
			{
				isPossible = false;
				break;
			}

			search = sm.suffix().first;
		}

		if (isPossible)
		{
			if (std::smatch sm; std::regex_search(split[0], sm, regexGame))
			{
				sum += std::stoi(sm[1].str());
			}
		}
	}
	std::cout << sum << std::endl;
}

void aoc::y2023::day02_part2()
{
	auto input = aoc::ParseInputFile<std::deque<std::string>>(aoc::GetInputPath(year, day));

	std::regex regex("(?:\\s?(\\d+) (\\w+),?;?)");

	int sum = 0;
	for (const auto& line : input)
	{
		std::map<std::string, int32_t> minCubes{
			{ "red", 0 },
			{ "green", 0 },
			{ "blue", 0 }
		};

		auto split = aoc::SplitString<std::deque<std::string>>(line, ": ");
		bool isPossible = true;
		int32_t lastNumShown = 0;
		auto search = split[1].cbegin();
		for (std::smatch sm; std::regex_search(search, split[1].cend(), sm, regex);)
		{
			if (minCubes[sm[2].str()] < std::stoi(sm[1].str()))
				minCubes[sm[2].str()] = std::stoi(sm[1].str());

			search = sm.suffix().first;
		}

		int product = 1;
		for (const auto& it : minCubes)
		{
			product *= it.second;
		}
		sum += product;
	}
	std::cout << sum << std::endl;

}