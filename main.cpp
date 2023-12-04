#include "src/2023/days.h"
#include "src/util.h"

static constexpr uint16_t year = 2023;
static constexpr uint8_t day = 4;
static constexpr uint8_t part = 2;
const static auto aocCalendar = std::map<uint16_t, std::deque<std::deque<std::function<void()>>>>
{
	{
		2023,
		{
			{ [&]() { aoc::y2023::day01_part1(); }, [&]() { aoc::y2023::day01_part2(); } },
			{ [&]() { aoc::y2023::day02_part1(); }, [&]() { aoc::y2023::day02_part2(); } },
			{ [&]() { aoc::y2023::day03_part1(); }, [&]() { aoc::y2023::day03_part2(); } },
			{ [&]() { aoc::y2023::day04_part1(); }, [&]() { aoc::y2023::day04_part2(); } },
		}
	}
};

int main()
{
	std::cout << "######################" << std::endl;
	std::cout << std::format("###### AoC {0} ######", year) << std::endl;
	std::cout << std::format("### Day {0} - Part {1} ###", day, part) << std::endl;
	std::cout << "######################" << std::endl << std::endl;

	size_t indexDay = static_cast<size_t>(day - 1);
	size_t indexPart = static_cast<size_t>(part - 1);
	aoc::SetInputData(year, day);

	auto start = std::chrono::high_resolution_clock::now();
	aocCalendar.at(year)[indexDay][indexPart]();
	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::nanoseconds diff = end - start;
	double diffSeconds = static_cast<double>(diff.count()) / 1000000000.0;

	std::cout << std::endl;
	std::cout << "######################" << std::endl;
	std::cout << "Execution Time: ";
	std::cout << std::format("{0} seconds", diffSeconds) << std::endl;
	std::cout << "######################" << std::endl << std::endl;
}