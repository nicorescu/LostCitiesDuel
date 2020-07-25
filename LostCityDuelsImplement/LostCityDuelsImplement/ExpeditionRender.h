#pragma once
#include <SFML/Graphics.hpp>
#include "CardRender.h"
#include "Expedition.h"
#include <vector>
#include <stack>


class ExpeditionRender
{
public:
	ExpeditionRender() = default;

	void AddToDiscardPile(CardRender& playerCard);
	void DrawFromDiscardPile();
	void Draw(sf::RenderWindow& window);
	void HighlightExpeditionCard();
	bool IsMouseOnExpeditionCard(CardRender card);
	void DrawCardOnDiscard(CardRender card, sf::RenderWindow& window);
	bool MouseIsOnDiscardPile();
	void ClearExpedition();


	void SetPlayer2PlayedCardsDisplay(Expedition chosenExpedition, sf::Font &font);
	void SetPlayer1PlayedCardsDisplay(Expedition chosenExpedition, sf::Font& font);
	void SetExpBox(float x, float y, float width, float height, std::string chosenTexture); 
	void SetDiscardBox(float width, float height, std::string chosenTexture);
	void SetExpeditionScoreBox1(float x,float y);
	void SetExpeditionScoreBox2(float x, float y);

	sf::RectangleShape GetExpeditionScoreBox1();
	sf::RectangleShape GetExpeditionScoreBox2();
	sf::RectangleShape& GetDiscardBox();
	sf::RectangleShape GetExpeditionBox();
	std::vector<CardRender>& GetPlayedCards();
	std::stack<CardRender>& GetDiscardPile();
	uint16_t GetColorIndex();

private:
	sf::RectangleShape m_expeditionBox;
	sf::RectangleShape m_discardPileBox;
	sf::RectangleShape m_expeditionScoreBox1;
	sf::RectangleShape m_expeditionScoreBox2;
private:
	sf::Texture m_background;
	sf::Texture m_pileTexture;
	sf::Texture m_scoreBoxTexture;
private:
	std::vector<CardRender> m_playedCardsDisplay;
	std::stack<CardRender> m_discardPileDisplay;
};

