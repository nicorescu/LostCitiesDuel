#include "Board.h"
#include <ctime>
#include<random>


Board::Board()
{
	
}

Board::~Board()
{
	for (int i = 0; i < 5; i++)
	{
		while (!m_discardPiles[i].empty())
			m_discardPiles[i].pop();
	}
}

std::vector<Card>& Board::GetDrawingDeck()
{
	return m_drawingDeck;
}

void Board::GenerateDrawingDeck()
{
	for (const auto& indexColour : { Card::Colour::gold,Card::Colour::blue,Card::Colour::white,Card::Colour::green,Card::Colour::red })
		for (const auto& indexValue : { Card::CardValues::secondCard,Card::CardValues::thirdCard,
			Card::CardValues::fourthCard,Card::CardValues::fifthCard,Card::CardValues::sixthCard,
			Card::CardValues::seventhCard,Card::CardValues::eighthCard,Card::CardValues::ninthCard,
			Card::CardValues::tenthCard })
		{
			EmplaceCard(Card((Card::Colour)indexColour,(Card::CardValues)indexValue));
		}
	for(int i=0;i<3;i++)
	for (const auto& indexColour : { Card::Colour::gold,Card::Colour::blue,Card::Colour::white,Card::Colour::green,Card::Colour::red })
		for(const auto &indexValue : {Card::CardValues::investition})
			EmplaceCard(Card((Card::Colour)indexColour,(Card::CardValues)indexValue));
	std::srand((unsigned int)time(0));
	std::random_device rng;
	std::mt19937 urng(rng());
	std::shuffle(m_drawingDeck.begin(), m_drawingDeck.end(), urng);
}


void Board::EmplaceCard(const Card& card)
{
	m_drawingDeck.emplace_back(card);
}

Card Board::ExtractCardFromDeck()
{
	Card currentCard = std::move(m_drawingDeck[m_drawingDeck.size()-1]);
	m_drawingDeck.erase(m_drawingDeck.end()-1);
	return currentCard;
}

void Board::GeneratePlayerHand(Player& chosenPlayer)
{
	for (int i = 0; i < 8; i++)
	{
		chosenPlayer.GetPlayerHand().push_back(m_drawingDeck[m_drawingDeck.size() - 1]);
		m_drawingDeck.pop_back();
	}
	chosenPlayer.SortHand();
}

std::stack<Card>& Board::GetPile(int index)
{
	return m_discardPiles.at(index);
}

bool Board::CheckForAllDiscardPiles()
{
	for (int i = 0; i < m_discardPiles.size(); i++)
		if (!m_discardPiles.at(i).empty())
			return 1;
	return 0;
}

Card Board::CheckSingleDiscardPile(int chosenExpedition)
{
	if (m_discardPiles.at(chosenExpedition).empty())
		return Card(Card::Colour::red, Card::CardValues::invalidCard);
	return m_discardPiles.at(chosenExpedition).top();
}

void Board::ResetBoard()
{
	for (int i = 0; i < 5; i++)
	{
		while (!m_discardPiles[i].empty())
			m_discardPiles[i].pop();
	}
}

void Board::PrintDiscardPiles()
{
	for (int i = 0; i < 5; i++)
	{
		switch (Card::Colour(i))
		{
		case Card::Colour::gold:
			std::cout<<"\n"<<i+1<<"->Gold: ";
			break;
		case Card::Colour::blue:
			std::cout << "\n" << i + 1 << "->Blue: ";
			break;
		case Card::Colour::white:
			std::cout << "\n" << i + 1 << "->White: ";
			break;
		case Card::Colour::green:
			std::cout << "\n" << i + 1 << "->Green: ";
			break;
		case Card::Colour::red:
			std::cout << "\n" << i + 1 << "->Red: ";
			break;
		}
		if (!m_discardPiles[i].empty())
			std::cout << m_discardPiles[i].top() << '\n';
		else std::cout << "Empty\n";
	}
}





