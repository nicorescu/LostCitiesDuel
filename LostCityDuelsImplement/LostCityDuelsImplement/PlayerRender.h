#include <iostream>
#include "SFML/Graphics.hpp"
#include "Board.h"
#include "ExpeditionRender.h"
class PlayerRender
{
public:
	void DrawExpeditionScores(sf::Font& font, Player& chosenPlayer, float x, float y, int index);
	void DrawPlayerHand(sf::RenderWindow& window);
	void DrawScores(sf::RenderWindow& window);

	int SelectCard();
	bool MouseIsOnAnyCard();
	void HighlightChosenCardForAWhile();
	void DrawCardFromDeck(Player& player, Board& board);

	void ClearHand();
	void SetNameAttributes(sf::Font& font, Player& chosenPlayer, float x, float y);
	void SetScoreAttributes(sf::Font& font, Player& chosenPlayer, float x, float y);
	void SetPlayerHandAttributes(Player& currentPlayer,sf::RenderWindow &window, sf::Font&font,float y);
	
	sf::Text GetName();
	sf::Text& GetScore();
	std::vector<CardRender>& GetCardsInHand();
	std::vector<sf::Text>& GetExpeditionScores();

	void CoverCards();
	void ShowCards(Player& currentPlayer, sf::Font& font);

private:
	sf::Texture m_hideHandTexture;
	std::vector<CardRender> m_cardsInHand;
	sf::Text m_playerNameDisplayed;
	sf::Text m_playerScore;
	std::vector<sf::Text> m_scorePerExpedition;

};

