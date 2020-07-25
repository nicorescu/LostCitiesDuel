#pragma once
#include "Card.h"
#include <cstdint>
#include <vector>
class Expedition
{
public:
	Expedition() = default;
	Expedition(const Card::Colour& expeditionColour);

	// Copy constructor
	Expedition(const Expedition& sourceExpedition);

	// Assigment operator overload
	Expedition operator=(const Expedition& secondExpedition);
	
	~Expedition();

	bool CardsAreInAscendingOrder(const Card& playedCard);
	std::vector<Card>& GetPlayedCards();
	uint16_t InvestmentCount();
	//void AddCard(Card& playedCard);
	int16_t SetScore(int index, uint16_t value);
	int16_t GetScore() const;
	Card::Colour GetColor();
	void ResetExpedition();

private:
	int16_t m_playerScore;
	Card::Colour m_expeditionColour;
	std::vector<Card>m_playedCards;
};

