#include "days.h"

void aoc::y2023::day06_part1()
{
	std::vector<std::pair<__int64, __int64>> races;
	for (const auto& line : aoc::GetInputData())
	{
		auto split = aoc::SplitString<std::deque<std::string>>(line, ": ");
		auto values = aoc::SplitStringRemoveEmpty<std::deque<std::string>>(split.back(), " ");
		int i = 0;
		for (const auto& value : values)
		{
			if (races.size() <= i)
				races.push_back({ std::stoll(value), 0ll });
			else
				races[i].second = std::stoll(value);
			i++;
		}
	}

	__int64 product = 1;
	for (const auto& race : races)
	{
		__int64 amountBeatable = 0;
		for (__int64 i = 0; i <= race.first; i++)
		{
			if ((race.first - i) * i > race.second)
				amountBeatable++;
		}
		product *= amountBeatable;
	}
	std::cout << product << std::endl;
}

void aoc::y2023::day06_part2()
{
	std::pair<__int64, __int64> race = { 0, 0 };
	for (const auto& line : aoc::GetInputData())
	{
		auto split = aoc::SplitString<std::deque<std::string>>(line, ": ");
		auto values = aoc::SplitStringRemoveEmpty<std::deque<std::string>>(split.back(), " ");
		std::string num = "";
		for (const auto& value : values)
		{
			num += value;
		}

		if (race.first == 0)
			race.first = std::stoll(num);
		else
			race.second = std::stoll(num);
	}

	__int64 sum = 0;
	for (__int64 i = 0; i <= race.first; i++)
	{
		if ((race.first - i) * i > race.second)
			sum++;
	}
	std::cout << sum << std::endl;
}