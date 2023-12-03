#include "src/2023/days.h"
#include "src/util.h"

static constexpr uint8_t day = 3;
static constexpr uint8_t part = 2;
const static auto aoc2023 = std::deque<std::deque<std::function<void()>>>
{
	{ [&]() { aoc::y2023::day01_part1(); }, [&]() { aoc::y2023::day01_part2(); } },
	{ [&]() { aoc::y2023::day02_part1(); }, [&]() { aoc::y2023::day02_part2(); } },
	{ [&]() { aoc::y2023::day03_part1(); }, [&]() { aoc::y2023::day03_part2(); } }
};

int main()
{
	size_t indexDay = static_cast<size_t>(day - 1);
	size_t indexPart = static_cast<size_t>(part - 1);
	aoc2023[indexDay][indexPart]();
}