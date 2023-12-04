#include "days.h"

static constexpr uint16_t year = 2023;
static constexpr uint8_t day = 3;

const aoc::Element* GetStart(const aoc::Element* pElement)
{
	auto curNode = pElement;

	// Go to start
	while (curNode->leftNode != nullptr && std::isdigit(curNode->leftNode->ch))
	{
		curNode = curNode->leftNode;
	}

	return curNode;
}

std::set<const aoc::Element*> GetNearbyDigit(const aoc::Element* pElement)
{
	std::set<const aoc::Element*> elements;
	if (pElement->leftNode != nullptr)
	{
		if (std::isdigit(pElement->leftNode->ch))
			elements.insert(GetStart(pElement->leftNode));

		if (pElement->leftNode->topNode != nullptr)
		{
			if (std::isdigit(pElement->leftNode->topNode->ch))
				elements.insert(GetStart(pElement->leftNode->topNode));
		}

		if (pElement->leftNode->bottomNode != nullptr)
		{
			if (std::isdigit(pElement->leftNode->bottomNode->ch))
				elements.insert(GetStart(pElement->leftNode->bottomNode));
		}
	}
	if (pElement->rightNode != nullptr)
	{
		if (std::isdigit(pElement->rightNode->ch))
			elements.insert(GetStart(pElement->rightNode));

		if (pElement->rightNode->topNode != nullptr)
		{
			if (std::isdigit(pElement->rightNode->topNode->ch))
				elements.insert(GetStart(pElement->rightNode->topNode));
		}

		if (pElement->rightNode->bottomNode != nullptr)
		{
			if (std::isdigit(pElement->rightNode->bottomNode->ch))
				elements.insert(GetStart(pElement->rightNode->bottomNode));
		}
	}

	if (pElement->topNode != nullptr)
	{
		if (std::isdigit(pElement->topNode->ch))
			elements.insert(GetStart(pElement->topNode));
	}

	if (pElement->bottomNode != nullptr)
	{
		if (std::isdigit(pElement->bottomNode->ch))
			elements.insert(GetStart(pElement->bottomNode));
	}

	return elements;
}

int BuildNumber(const aoc::Element* pElement)
{
	auto curNode = pElement;

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
	InputNodedMap inputNodedMap;
	inputNodedMap.FromInput(aoc::GetInputData());

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
	InputNodedMap inputNodedMap;
	inputNodedMap.FromInput(aoc::GetInputData());

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
