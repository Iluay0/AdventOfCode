#include "days.h"

void aoc::y2023::day04_part1()
{
	std::regex regex("Card\\s+?(\\d+): (.*)");

	__int64 sum = 0;
	for (const auto& line : aoc::GetInputData())
	{
		std::smatch sm;
		std::regex_search(line, sm, regex);

		auto split = aoc::SplitString<std::deque<std::string>>(sm[2], "|");
		auto winningNumbers = aoc::SplitStringRemoveEmpty<std::vector<std::string>>(split.front(), " ");
		auto ownNumbers = aoc::SplitStringRemoveEmpty<std::vector<std::string>>(split.back(), " ");

		std::sort(winningNumbers.begin(), winningNumbers.end());
		std::sort(ownNumbers.begin(), ownNumbers.end());

		std::vector<std::string> intersections;
		std::set_intersection(
			winningNumbers.begin(), winningNumbers.end(),
			ownNumbers.begin(), ownNumbers.end(),
			std::back_inserter(intersections)
		);

		if (intersections.size() > 0)
			sum += static_cast<__int64>(pow(2, intersections.size() - 1));
	}
	std::cout << sum << std::endl;
}

void aoc::y2023::day04_part2()
{
	std::map<int, int> mapAdditionalCards;
	std::regex regex("Card\\s+?(\\d+): (.*)");

	int rolls = 0;
	for (const auto& line : aoc::GetInputData())
	{
		std::smatch sm;
		std::regex_search(line, sm, regex);

		int cardNum = std::stoi(sm[1]);
		int cardRolls = mapAdditionalCards[cardNum] + 1;

		auto split = aoc::SplitString<std::deque<std::string>>(sm[2], "|");
		auto winningNumbers = aoc::SplitStringRemoveEmpty<std::vector<std::string>>(split.front(), " ");
		auto ownNumbers = aoc::SplitStringRemoveEmpty<std::vector<std::string>>(split.back(), " ");

		std::sort(winningNumbers.begin(), winningNumbers.end());
		std::sort(ownNumbers.begin(), ownNumbers.end());

		std::vector<std::string> intersections;
		std::set_intersection(
			winningNumbers.begin(), winningNumbers.end(),
			ownNumbers.begin(), ownNumbers.end(),
			std::back_inserter(intersections)
		);

		rolls += cardRolls;

		for (int i = 1; i <= static_cast<int>(intersections.size()); i++)
		{
			mapAdditionalCards[cardNum + i] += cardRolls;
		}
	}
	std::cout << rolls << std::endl;
}
