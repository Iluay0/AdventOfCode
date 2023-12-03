#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <deque>
#include <string>
#include <functional>
#include <format>
#include <regex>

namespace aoc
{
	inline std::string GetInputPath(uint16_t year, uint8_t day)
	{
		return std::format("input/{:04}/day{:02}.txt", year, day);
	}

	template <typename T>
	inline T ParseInputFile(std::string inputFile)
	{
		std::ifstream ifs(inputFile, std::ifstream::in);

		T inputs{};
		for (std::string line; std::getline(ifs, line); )
		{
			inputs.push_back(line);
		}

		return inputs;
	}

	template <typename T>
	inline T SplitString(std::string str, std::string delimiter)
	{
		T strings{};

		std::string::size_type pos = 0;
		std::string::size_type prev = 0;
		while ((pos = str.find(delimiter, prev)) != std::string::npos)
		{
			strings.push_back(str.substr(prev, pos - prev));
			prev = pos + delimiter.size();
		}
		strings.push_back(str.substr(prev));

		return strings;
	}

	template <typename T>
	inline std::string Join(T list, std::string delimiter)
	{
		std::string str = "";
		for (auto& it : list)
			str += it + delimiter;
		return str;
	}

	template <typename T>
	inline int Sum(T list)
	{
		int sum = 0;
		for (auto& it : list)
			sum += it;
		return sum;
	}

	inline int BinaryToInt(long long n)
	{
		int dec = 0, i = 0, rem;

		while (n != 0) {
			rem = n % 10;
			n /= 10;
			dec += rem * pow(2, i);
			++i;
		}

		return dec;
	}

	inline void ReplaceAll(std::string& str, const std::string& from, const std::string& to)
	{
		if (from.empty())
			return;
		size_t startPos = 0;
		while ((startPos = str.find(from, startPos)) != std::string::npos)
		{
			str.replace(startPos, from.length(), to);
			startPos += to.length();
		}
	}

	inline bool IsNumber(std::string str)
	{
		return !str.empty() && std::find_if(str.begin(),
			str.end(), [](unsigned char c) { return !std::isdigit(c); }) == str.end();
	}
}