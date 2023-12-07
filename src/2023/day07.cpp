#include "days.h"

static std::string cardValues = "AKQJT98765432";
static std::string cardValuesP2 = "AKQT98765432J";
static int part = 1;

struct Hand
{
	std::map<char, int> cards;
	std::vector<std::pair<char, int>> cardsVec;
	std::string cardsOrder = "";
	__int64 bid = 0ll;
	__int64 score = 0;

	void Initialize()
	{
		InitCardsVec();
		if (part == 2)
			HandleJokers();
		score = GetScore();
	}

	void AddCard(char card)
	{
		if (cards.count(card))
			cards[card]++;
		else
			cards[card] = 1;
		cardsOrder.push_back(card);
	}

	void InitCardsVec()
	{
		if (cardsVec.empty())
		{
			cardsVec = { cards.begin(), cards.end() };
			std::sort(cardsVec.begin(), cardsVec.end(),
				[](const std::pair<char, int>& a, const std::pair<char, int>& b) {
					return a.second > b.second;
				});
		}
	}

	void HandleJokers()
	{
		if (!cards.count('J'))
			return;

		for (const auto& it : cardsVec)
		{
			if (it.first == 'J')
				continue;

			cards[it.first] += cards['J'];
			cards['J'] = 0;
			cardsVec.clear();
			InitCardsVec();
			return;
		}
	}

	__int64 GetScore()
	{
		bool threeOfAKind = false;
		bool twoOfAKind = false;
		for (const auto& [card, amount] : cardsVec)
		{
			if (amount == 5)
				return 7;
			if (amount == 4)
				return 6;
			if (amount == 3)
			{
				if (twoOfAKind)
					return 5;
				threeOfAKind = true;
				continue;
			}
			if (amount == 2)
			{
				if (threeOfAKind)
					return 5;
				if (twoOfAKind)
					return 3;
				twoOfAKind = true;
				continue;
			}
		}
		if (threeOfAKind)
			return 4;
		if (twoOfAKind)
			return 2;
		return 1;
	}

	static __int64 GetValue(char card)
	{
		if(part == 2)
			return std::find(cardValuesP2.begin(), cardValuesP2.end(), card) - cardValuesP2.begin();
		return std::find(cardValues.begin(), cardValues.end(), card) - cardValues.begin();
	}

	bool operator<(Hand other)
	{
		if (score != other.score)
			return score < other.score;
		for (int i = 0; i < 5; i++)
		{
			if (cardsOrder[i] != other.cardsOrder[i])
				return Hand::GetValue(cardsOrder[i]) > Hand::GetValue(other.cardsOrder[i]);
		}
		return true;
	}
};

void aoc::y2023::day07_part1()
{
	std::vector<Hand> hands;
	for (const auto& line : aoc::GetInputData())
	{
		Hand hand;
		auto split = aoc::SplitString<std::deque<std::string>>(line, " ");
		hand.bid = std::stoll(split.back());
		for (const auto& ch : split.front())
		{
			hand.AddCard(ch);
		}
		hand.Initialize();
		hands.push_back(hand);
	}

	std::sort(hands.begin(), hands.end(),
		[&](Hand& a, Hand& b) {
			return a < b;
		});

	__int64 sum = 0;
	__int64 i = 1;
	for (const auto& hand : hands)
	{
		sum += hand.bid * i;
		i++;
	}
	std::cout << sum << std::endl;
}

void aoc::y2023::day07_part2()
{
	part = 2;

	std::vector<Hand> hands;
	for (const auto& line : aoc::GetInputData())
	{
		Hand hand;
		auto split = aoc::SplitString<std::deque<std::string>>(line, " ");
		hand.bid = std::stoll(split.back());
		for (const auto& ch : split.front())
		{
			hand.AddCard(ch);
		}
		hand.Initialize();
		hands.push_back(hand);
	}

	std::sort(hands.begin(), hands.end(),
		[&](Hand& a, Hand& b) {
			return a < b;
		});

	__int64 sum = 0;
	__int64 i = 1;
	for (const auto& hand : hands)
	{
		sum += hand.bid * i;
		i++;
	}
	std::cout << sum << std::endl;
}