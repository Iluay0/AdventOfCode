#include "days.h"

void aoc::y2023::day04_part1()
{
	std::regex regex("Card\\s+?(\\d+): (.*)");

	__int64 sum = 0;
	for (const auto& line : aoc::GetInputData())
	{
		std::smatch sm;
		if (!std::regex_search(line, sm, regex))
		{
			std::cout << "Regex failed for: " << line;
			continue;
		}

		auto split = aoc::SplitString<std::deque<std::string>>(sm[2], "|");
		auto winningNumbers = aoc::SplitStringRemoveEmpty<std::deque<std::string>>(split.front(), " ");
		auto ownNumbers = aoc::SplitStringRemoveEmpty<std::deque<std::string>>(split.back(), " ");

		int power = -1;
		for (auto& winningNumber : winningNumbers)
		{
			auto it = std::find_if(ownNumbers.begin(), ownNumbers.end(),
				[&winningNumber](const std::string& number) {
					return number == winningNumber;
				});
			if (it != ownNumbers.end())
				power++;
		}

		if (power >= 0)
			sum += static_cast<__int64>(pow(2, power));
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
		if (!std::regex_search(line, sm, regex))
		{
			std::cout << "Regex failed for: " << line;
			continue;
		}

		int cardNum = std::stoi(sm[1]);
		int cardRolls = mapAdditionalCards[cardNum] + 1;

		auto split = aoc::SplitString<std::deque<std::string>>(sm[2], "|");
		auto winningNumbers = aoc::SplitStringRemoveEmpty<std::deque<std::string>>(split.front(), " ");
		auto ownNumbers = aoc::SplitStringRemoveEmpty<std::deque<std::string>>(split.back(), " ");

		int wins = 0;
		for (auto& winningNumber : winningNumbers)
		{
			auto it = std::find_if(ownNumbers.begin(), ownNumbers.end(),
				[&winningNumber](const std::string& number) {
					return number == winningNumber;
				});
			if (it != ownNumbers.end())
				wins++;
		}
		rolls += cardRolls;

		for (int i = 1; i <= wins; i++)
		{
			mapAdditionalCards[cardNum + i] += cardRolls;
		}
	}
	std::cout << rolls << std::endl;
}
