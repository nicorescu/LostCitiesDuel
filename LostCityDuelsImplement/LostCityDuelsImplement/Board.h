#pragma once
#include "Player.h"

#include <stack>
#include <vector>
#include <array>


class Board
{
public:
	Board();
	~Board();
	std::vector <Card>& GetDrawingDeck();
	void GenerateDrawingDeck();
	void EmplaceCard(const Card& card);
	Card ExtractCardFromDeck();
	void GeneratePlayerHand(Player& chosenPlayer);
	std::stack<Card>& GetPile(int index);
	bool CheckForAllDiscardPiles();
	Card CheckSingleDiscardPile(int chosenExpedition);
	void ResetBoard();
	void PrintDiscardPiles();

private:
	std::array<std::stack<Card>, 5> m_discardPiles;
    std::vector <Card> m_drawingDeck;

};

