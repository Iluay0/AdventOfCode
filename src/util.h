#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <deque>
#include <string>
#include <functional>
#include <format>
#include <regex>
#include <set>
#include <future>

namespace aoc
{
	struct Element
	{
		char ch;
		int16_t x;
		int16_t y;

		Element* topNode = nullptr;
		Element* leftNode = nullptr;
		Element* rightNode = nullptr;
		Element* bottomNode = nullptr;

		Element(char ch, const int16_t& x, const int16_t& y)
			: ch(ch), x(x), y(y)
		{
		}
	};

	class InputNodedMap : public std::map<std::pair<int16_t, int16_t>, Element>
	{
	public:
		void InsertElement(int16_t x, int16_t y, Element element)
		{
			auto it = insert({ {y, x}, element });
			Element* pElement = &it.first->second;
			if (x > 0)
			{
				pElement->leftNode = &find({ y, x - 1 })->second;
				pElement->leftNode->rightNode = pElement;
			}
			if (y > 0)
			{
				pElement->topNode = &find({ y - 1, x })->second;
				pElement->topNode->bottomNode = pElement;
			}
		}

		void FromInput(std::deque<std::string> input)
		{
			clear();

			int16_t y = 0;
			for (const auto& line : input)
			{
				int16_t x = 0;
				for (const auto& ch : line)
				{
					InsertElement(x, y, Element(ch, x, y));
					x++;
				}
				y++;
			}
		}
	};

	struct InputData
	{
		std::deque<std::string> input;
		static InputData* Inst()
		{
			static InputData inst;
			return &inst;
		}
	};

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
	inline T SplitStringRemoveEmpty(std::string str, std::string delimiter)
	{
		T strings = SplitString<T>(str, delimiter);

		strings.erase(std::remove_if(strings.begin(), strings.end(),
			[](const std::string& str) {
				return str == "";
			}), strings.end());

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
			dec += static_cast<int>(static_cast<double>(rem) * pow(2, i));
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

	inline std::deque<std::string> GetInputData()
	{
		return InputData::Inst()->input;
	}

	inline void SetInputData(int16_t year, int8_t day)
	{
		InputData::Inst()->input = aoc::ParseInputFile<std::deque<std::string>>(aoc::GetInputPath(year, day));
	}

	inline std::string Trim(std::string s)
	{
		std::string::const_iterator it = s.begin();
		while (it != s.end() && isspace(*it))
			it++;

		std::string::const_reverse_iterator rit = s.rbegin();
		while (rit.base() != it && isspace(*rit))
			rit++;

		return std::string(it, rit.base());
	}

	inline __int64 gcd(__int64 a, __int64 b)
	{
		return b == 0ll ? a : gcd(b, a % b);
	}

	inline __int64 gcd(std::deque<__int64> numbers)
	{
		__int64 result = numbers.front();
		for (const auto& it : numbers)
			result = gcd(result, it);
		return result;
	}

	inline __int64 lcm(__int64 a, __int64 b)
	{
		return abs(a * b) / gcd(a, b);
	}

	inline __int64 lcm(std::deque<__int64> numbers)
	{
		if (numbers.size() == 2)
			return lcm(numbers.front(), numbers.back());
		__int64 front = numbers.front();
		numbers.pop_front();
		return lcm(front, lcm(numbers));
	}
}