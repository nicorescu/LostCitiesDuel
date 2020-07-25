#include<iostream>
#include "Card.h"
#include <SFML/Graphics.hpp>
#include <string>
class CardRender
{
public:
	CardRender();
	CardRender(const Card &card, sf::Font& font);

	bool MouseIsOnCard();
	void HighlightCard();
	void Draw(sf::RenderWindow& window);

	void SetCardAttributes(const Card& card);
	void SetCardPosition(float x, float y);
	void SetCardSizes(float width, float height);
	void SetText(const Card& card, sf::Font& font);

	uint16_t GetColorIndex() const;
	sf::RectangleShape& GetCardDisplay();
	sf::Text& GetCardSymbol();
private:
	sf::RectangleShape m_cardDisplay;
	sf::Text m_cardSymbol;
};

