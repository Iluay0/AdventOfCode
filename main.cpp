#include "src/2023/days.h"
#include "src/util.h"

static constexpr uint8_t day = 1;
static constexpr uint8_t part = 2;
const static auto aoc2023 = std::deque<std::deque<std::function<void()>>>
{
	{ [&]() { aoc::y2023::day01_part1(); }, [&]() { aoc::y2023::day01_part2(); } },
	{ [&]() { aoc::y2023::day02_part1(); }, [&]() { aoc::y2023::day02_part2(); } },
	{ [&]() { aoc::y2023::day03_part1(); }, [&]() { aoc::y2023::day03_part2(); } }
};

int main()
{
	std::cout << "######################" << std::endl;
	std::cout << "### Advent of Code ###" << std::endl;
	std::cout << std::format("### Day {0} - Part {1} ###", day, part) << std::endl;
	std::cout << "######################" << std::endl << std::endl;

	auto start = std::chrono::high_resolution_clock::now();

	size_t indexDay = static_cast<size_t>(day - 1);
	size_t indexPart = static_cast<size_t>(part - 1);
	aoc2023[indexDay][indexPart]();

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::nanoseconds diff = end - start;
	double diffSeconds = static_cast<double>(diff.count()) / 1000000000.0;

	std::cout << std::endl;
	std::cout << "######################" << std::endl;
	std::cout << "Execution Time: ";
	std::cout << std::format("{0} seconds", diffSeconds) << std::endl;
	std::cout << "######################" << std::endl << std::endl;
}