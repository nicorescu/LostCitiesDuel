#pragma once
#include<SFML/Graphics.hpp>
#include"ExpeditionRender.h"
#include "Board.h"
#include "PlayerRender.h"
#include<array>
class BoardDisplay
{
public:
	void DrawScoreBoxes(sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
	void GenerateExpeditions(sf::RenderWindow& window);
	void GenerateDrawingDeckTexture(sf::RenderWindow& window);
	void GenerateTopBar(sf::RenderWindow& window);
	void GenerateBottomBar(sf::RenderWindow& window);
	void GenerateNumberOfCardsInDeck(sf::Font& font,int number, float x, float y);
	void HighlightExpeditionsCard();

	bool MouseIsOnAnyDiscardPile();
	bool MouseIsOnDrawingDeck();
	bool MouseIsOnExpedition();
	bool MouseIsOnACertainDiscardPile(uint16_t cardColorIndex);
	bool MouseIsOnACertainExpedition(uint16_t cardColorIndex);

	int SelectDiscPile();

	void SetNumberOfCardsInDeck(int number);

	sf::Text GetNumberOfCardsInDeck();
	std::array<ExpeditionRender, 5>& GetExpeditions();
	sf::RectangleShape* GetBottomBar();
	sf::RectangleShape* GetTopBar();
	sf::RectangleShape* GetDrawingDeckShape();
	std::stack<CardRender>& GetDrawingDeck();
private:
	std::array<ExpeditionRender, 5> m_expeditionsDisplay;
	std::stack<CardRender> m_drawingDeck;
	sf::RectangleShape* m_drawingDeckShape;
	sf::RectangleShape* m_topBar;
	sf::RectangleShape* m_bottomBar;
	sf::Text numberOfCards;
	sf::Texture m_barTexture;
	sf::Texture m_DrawingDeckTexture;
	sf::Text m_numberOfCardsInDeck;
};

