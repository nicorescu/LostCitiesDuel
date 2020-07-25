#include "Expedition.h"

Expedition::Expedition(const Card::Colour& expeditionColour)
	:m_expeditionColour(expeditionColour)
{
	m_playerScore = 0;
}

Expedition::Expedition(const Expedition& sourceExpedition)
{
	m_playerScore = sourceExpedition.m_playerScore;
	m_playedCards = sourceExpedition.m_playedCards;
	m_expeditionColour = sourceExpedition.m_expeditionColour;
}

Expedition Expedition::operator=(const Expedition& secondExpedition)
{
	if (this == &secondExpedition)
		return *this;
	m_playerScore = secondExpedition.m_playerScore;
	m_playedCards = secondExpedition.m_playedCards;
	m_expeditionColour = secondExpedition.m_expeditionColour;
	return *this;
}

Expedition::~Expedition() 
{
	m_playerScore = 0;
	while (!m_playedCards.empty())
	{
		m_playedCards.pop_back();
	}
}

bool Expedition::CardsAreInAscendingOrder(const Card& playedCard)
{
	if(m_playedCards.size()>0)
		return playedCard.GetValue() >= m_playedCards[m_playedCards.size() - 1].GetValue();
	return true;
}

std::vector<Card>& Expedition::GetPlayedCards()
{
	return m_playedCards;
}

uint16_t Expedition::InvestmentCount()
{
	int count = 1;
	for (int index = 0; index < m_playedCards.size(); index++)
		if (m_playedCards[index].GetValue() == Card::CardValues::investition)
			count++;
	return count;
}

int16_t Expedition::SetScore(int index, uint16_t value)
{
	int multiplier = InvestmentCount();
	int16_t startCost = -20;
	if (m_playedCards.size() == 1)
	{
		if (value == 1)
			m_playerScore = startCost * multiplier;
		else
			m_playerScore += startCost + value;
	}
	else if (m_playedCards.size() == 8)
		m_playerScore += (value + 20) * multiplier;
	else if (value == 1)
		m_playerScore = startCost * multiplier;
	else
		m_playerScore += value * multiplier;
	return m_playerScore;
}

int16_t Expedition::GetScore() const
{
	return m_playerScore;
}

Card::Colour Expedition::GetColor()
{
	return m_expeditionColour;
}

void Expedition::ResetExpedition()
{
	m_playerScore = 0;
	while (!m_playedCards.empty())
	{
		m_playedCards.pop_back();
	}
}

