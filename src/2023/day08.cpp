#include "days.h"

struct Location
{
	std::string name;
	std::string left;
	std::string right;

	Location(const std::string& name, const std::string& left, const std::string& right)
		: name(name), left(left), right(right)
	{
	}

	Location() = default;
};

void aoc::y2023::day08_part1()
{
	std::map<std::string, Location> locations;
	auto input = aoc::GetInputData();

	auto directions = input.front();
	input.pop_front();
	input.pop_front();

	for (const auto& line : input)
	{
		auto split = aoc::SplitString<std::deque<std::string>>(line, " ");
		std::erase(split[2], '(');
		std::erase(split[2], ',');
		std::erase(split[3], ')');
		locations.insert({ split[0], Location(split[0], split[2], split[3]) });
	}

	std::string current = "AAA";
	size_t i = 0;
	while (current != "ZZZ")
	{
		if (directions[i % directions.size()] == 'L')
			current = locations[current].left;
		else if (directions[i % directions.size()] == 'R')
			current = locations[current].right;
		i++;
	}

	std::cout << i << std::endl;
}

__int64 GetLoopingPathSize(std::string current, std::string directions, std::map<std::string, Location>& locations)
{
	std::string prevPath = "";
	std::string path = current;

	size_t i = 0;
	while (true)
	{
		std::string prevLocation = current;

		if (directions[i % directions.size()] == 'L')
			current = locations[current].left;
		else if (directions[i % directions.size()] == 'R')
			current = locations[current].right;

		i++;

		path += current;
		if (path.back() == 'Z')
		{
			if (prevPath.contains(path) || prevLocation == current)
				return i - (path.size() / 3ll);
			prevPath += path;
			path = "";
		}
	}

	return 0;
}

void aoc::y2023::day08_part2()
{
	std::map<std::string, Location> locations;
	auto input = aoc::GetInputData();

	auto directions = input.front();
	input.pop_front();
	input.pop_front();

	std::deque<std::string> currentLocations;
	for (const auto& line : input)
	{
		auto split = aoc::SplitString<std::deque<std::string>>(line, " ");
		std::erase(split[2], '(');
		std::erase(split[2], ',');
		std::erase(split[3], ')');
		locations.insert({ split[0], Location(split[0], split[2], split[3]) });

		if (split[0].back() == 'A')
			currentLocations.push_back(split[0]);
	}

	std::deque<std::future<__int64>> futures;
	for (const auto& it : currentLocations)
	{
		futures.push_back(std::async(std::launch::async, [&] { return GetLoopingPathSize(it, directions, locations); }));
	}

	std::deque<__int64> paths;
	for (auto& it : futures)
	{
		paths.push_back(it.get());
	}

	__int64 gcd = aoc::gcd(paths);
	for (auto& it : paths)
	{
		it /= (gcd / directions.size());
	}

	std::cout << aoc::lcm(paths) << std::endl;
}