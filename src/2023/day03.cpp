#include "days.h"

static constexpr uint16_t year = 2023;
static constexpr uint8_t day = 3;

const aoc::Element* GetStart(const aoc::Element* element)
{
	auto curNode = element;

	// Go to start
	while (curNode->leftNode != nullptr && std::isdigit(curNode->leftNode->ch))
	{
		curNode = curNode->leftNode;
	}

	return curNode;
}

std::set<const aoc::Element*> GetNearbyDigit(const aoc::Element* element)
{
	std::set<const aoc::Element*> elements;
	if (element->leftNode != nullptr)
	{
		if (std::isdigit(element->leftNode->ch))
			elements.insert(GetStart(element->leftNode));

		if (element->leftNode->topNode != nullptr)
		{
			if (std::isdigit(element->leftNode->topNode->ch))
				elements.insert(GetStart(element->leftNode->topNode));
		}

		if (element->leftNode->bottomNode != nullptr)
		{
			if (std::isdigit(element->leftNode->bottomNode->ch))
				elements.insert(GetStart(element->leftNode->bottomNode));
		}
	}
	if (element->rightNode != nullptr)
	{
		if (std::isdigit(element->rightNode->ch))
			elements.insert(GetStart(element->rightNode));

		if (element->rightNode->topNode != nullptr)
		{
			if (std::isdigit(element->rightNode->topNode->ch))
				elements.insert(GetStart(element->rightNode->topNode));
		}

		if (element->rightNode->bottomNode != nullptr)
		{
			if (std::isdigit(element->rightNode->bottomNode->ch))
				elements.insert(GetStart(element->rightNode->bottomNode));
		}
	}

	if (element->topNode != nullptr)
	{
		if (std::isdigit(element->topNode->ch))
			elements.insert(GetStart(element->topNode));
	}

	if (element->bottomNode != nullptr)
	{
		if (std::isdigit(element->bottomNode->ch))
			elements.insert(GetStart(element->bottomNode));
	}

	return elements;
}

int BuildNumber(const aoc::Element* element)
{
	auto curNode = element;

	std::string szNum = { curNode->ch };
	while (curNode->rightNode != nullptr && std::isdigit(curNode->rightNode->ch))
	{
		szNum.push_back(curNode->rightNode->ch);
		curNode = curNode->rightNode;
	}

	return std::stoi(szNum);
}

void aoc::y2023::day03_part1()
{
	auto input = aoc::ParseInputFile<std::deque<std::string>>(aoc::GetInputPath(year, day));

	InputNodedMap inputNodedMap;
	inputNodedMap.FromInput(input);

	int32_t sum = 0;
	for (const auto& [pos, element] : inputNodedMap)
	{
		if (std::isdigit(element.ch) || element.ch == '.')
			continue;

		for (const auto& it : GetNearbyDigit(&element))
		{
			sum += BuildNumber(it);
		}
	}
	std::cout << sum << std::endl;
}

void aoc::y2023::day03_part2()
{
	auto input = aoc::ParseInputFile<std::deque<std::string>>(aoc::GetInputPath(year, day));

	InputNodedMap inputNodedMap;
	inputNodedMap.FromInput(input);

	int32_t sum = 0;
	for (const auto& [pos, element] : inputNodedMap)
	{
		if (element.ch != '*')
			continue;

		int product = 1;
		auto nearbyDigits = GetNearbyDigit(&element);
		if (nearbyDigits.size() > 1)
		{
			for (const auto& it : nearbyDigits)
			{
				product *= BuildNumber(it);
			}
			sum += product;
		}
	}
	std::cout << sum << std::endl;
}
