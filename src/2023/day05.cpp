#include "days.h"

struct StoredProcess
{
	__int64 value;
	bool hasStepped;

	bool operator<(StoredProcess other) const
	{
		return value < other.value;
	}

	StoredProcess(__int64 value, bool hasStepped)
		: value(value), hasStepped(hasStepped)
	{
	}
};

struct StoredProcessP2
{
	__int64 value;
	__int64 range;
	bool hasStepped;

	bool operator<(StoredProcessP2 other) const
	{
		return value < other.value;
	}

	StoredProcessP2(__int64 value, __int64 range, bool hasStepped)
		: value(value), range(range), hasStepped(hasStepped)
	{
	}

	__int64 GetRangeEnd()
	{
		return value + range;
	}
};

void aoc::y2023::day05_part1()
{
	std::vector<StoredProcess> storedProcesses;
	for (const auto& line : aoc::GetInputData())
	{
		if (line == "")
			continue;

		if (line.contains("map:"))
		{
			for (auto& storedProcess : storedProcesses)
			{
				storedProcess.hasStepped = false;
			}
			continue;
		}

		if (line.contains("seeds:"))
		{
			auto split = aoc::SplitString<std::deque<std::string>>(line, ": ");
			auto seedNumbers = aoc::SplitStringRemoveEmpty<std::deque<std::string>>(split.back(), " ");
			for (const auto& seedNumber : seedNumbers)
			{
				storedProcesses.push_back(StoredProcess(std::stoll(seedNumber), false));
			}
		}
		else
		{
			auto split = aoc::SplitString<std::deque<std::string>>(line, " ");
			__int64 dstRangeStart = std::stoll(split[0]);
			__int64 srcRangeStart = std::stoll(split[1]);
			__int64 srcRangeEnd = srcRangeStart + std::stoll(split[2]);
			for (auto& storedProcess : storedProcesses)
			{
				if (storedProcess.hasStepped)
					continue;

				if (storedProcess.value >= srcRangeStart && storedProcess.value < srcRangeEnd)
				{
					storedProcess.value += (dstRangeStart - srcRangeStart);
					storedProcess.hasStepped = true;
				}
			}
		}
	}

	std::sort(storedProcesses.begin(), storedProcesses.end(), std::less());
	std::cout << storedProcesses.front().value << std::endl;
}

void aoc::y2023::day05_part2()
{
	std::vector<StoredProcessP2> storedProcesses;
	for (const auto& line : aoc::GetInputData())
	{
		if (line == "")
			continue;

		if (line.contains("map:"))
		{
			for (auto& storedProcess : storedProcesses)
			{
				storedProcess.hasStepped = false;
			}
			continue;
		}

		if (line.contains("seeds:"))
		{
			auto split = aoc::SplitString<std::deque<std::string>>(line, ": ");
			auto values = aoc::SplitStringRemoveEmpty<std::deque<std::string>>(split.back(), " ");
			__int64 prevValue = 0;
			for (const auto& value : values)
			{
				if (prevValue == 0)
					prevValue = std::stoll(value);
				else
				{
					storedProcesses.push_back(StoredProcessP2(prevValue, std::stoll(value), false));
					prevValue = 0;
				}
			}
		}
		else
		{
			auto split = aoc::SplitString<std::deque<std::string>>(line, " ");
			__int64 dstRangeStart = std::stoll(split[0]);
			__int64 srcRangeStart = std::stoll(split[1]);
			__int64 srcRangeEnd = srcRangeStart + std::stoll(split[2]);
			for (auto& storedProcess : storedProcesses)
			{
				if (storedProcess.hasStepped)
					continue;

				if (srcRangeStart <= storedProcess.value && srcRangeEnd >= storedProcess.GetRangeEnd())
				{
					storedProcess.value += (dstRangeStart - srcRangeStart);
					storedProcess.hasStepped = true;
				}
				else if (srcRangeStart >= storedProcess.value && srcRangeStart < storedProcess.GetRangeEnd())
				{
					__int64 prevRange = storedProcess.range;
					__int64 prevValue = storedProcess.value;
					storedProcess.range = srcRangeStart - storedProcess.value;
//					storedProcess.hasStepped = true;

					StoredProcessP2 newProcess(dstRangeStart, prevRange - storedProcess.range, true);
					storedProcesses.push_back(newProcess);
				}
				else if (srcRangeEnd >= storedProcess.value && srcRangeEnd < storedProcess.GetRangeEnd())
				{
					__int64 prevRange = storedProcess.range;
					__int64 prevValue = storedProcess.value;
					storedProcess.range = storedProcess.range - (srcRangeEnd - storedProcess.value);
					storedProcess.value = srcRangeEnd;
//					storedProcess.hasStepped = true;

					StoredProcessP2 newProcess(prevValue - (srcRangeStart - dstRangeStart), prevRange - storedProcess.range, true);
					storedProcesses.push_back(newProcess);
				}
			}
		}
	}

	std::sort(storedProcesses.begin(), storedProcesses.end(), std::less());
	std::cout << storedProcesses.front().value << std::endl;
}