#include <iostream>
#include "SFML/Graphics.hpp"
#include "Player.h"
#include "BoardDisplay.h"
class PlayerDisplay
{

public:


	std::vector<sf::RectangleShape> GetCardsInHand();
	sf::Text GetPlayerNameDisplayed();
	void SetPlayerNameDisplayed(sf::Text& name);
	void DisplayHand(Player & currentPlayingPlayer,BoardDisplay& board);
private:

	std::vector<sf::RectangleShape> m_cardsInHand;
	std::vector<sf::Text> m_cardsNumber;
	sf::Text m_playerNameDisplayed;
};

