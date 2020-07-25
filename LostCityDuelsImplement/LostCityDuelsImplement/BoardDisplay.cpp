#include "BoardDisplay.h"
#include<fstream>

void BoardDisplay::GenerateTopBar(sf::RenderWindow& window)
{
	m_topBar = new sf::RectangleShape(sf::Vector2f(window.getSize().x, window.getSize().y/10));
	m_barTexture.loadFromFile("HandBackground1.jpg");
	m_topBar->setTexture(&m_barTexture);
	m_topBar->setPosition(window.getPosition().x, window.getPosition().y);
}
void BoardDisplay::GenerateBottomBar(sf::RenderWindow& window)
{
	m_bottomBar = new sf::RectangleShape(sf::Vector2f(window.getSize().x, window.getSize().y/10));
	m_barTexture.loadFromFile("HandBackground1.jpg");
	m_bottomBar->setTexture(&m_barTexture);
	m_bottomBar->setPosition(window.getPosition().x, window.getSize().y - (window.getSize().y/10));
}
void BoardDisplay::GenerateNumberOfCardsInDeck(sf::Font& font, int number, float x, float y)
{
	m_numberOfCardsInDeck.setFont(font);
	m_numberOfCardsInDeck.setCharacterSize(25);
	m_numberOfCardsInDeck.setString(std::to_string(number));
	m_numberOfCardsInDeck.setPosition(x, y);
}
void BoardDisplay::HighlightExpeditionsCard()
{
	for (int i = 0; i < m_expeditionsDisplay.size(); i++)
		m_expeditionsDisplay[i].HighlightExpeditionCard();
}



bool BoardDisplay::MouseIsOnDrawingDeck()
{
	sf::Mouse mouse;
	if (mouse.getPosition().x >= m_drawingDeckShape->getPosition().x && mouse.getPosition().x <= (m_drawingDeckShape->getPosition().x + m_drawingDeckShape->getSize().x)
		&& mouse.getPosition().y >= m_drawingDeckShape->getPosition().y && mouse.getPosition().y <= (m_drawingDeckShape->getPosition().y + m_drawingDeckShape->getSize().y))
		return true;
	return false;
}

bool BoardDisplay::MouseIsOnExpedition()
{
	sf::Mouse mouse;
	for (int i = 0; i < m_expeditionsDisplay.size(); i++)
		if (mouse.getPosition().x >= m_expeditionsDisplay[i].GetExpeditionBox().getPosition().x && mouse.getPosition().x <= m_expeditionsDisplay[i].GetExpeditionBox().getPosition().x + (m_expeditionsDisplay[i].GetExpeditionBox().getSize().x)
			&& mouse.getPosition().y >= m_expeditionsDisplay[i].GetExpeditionBox().getPosition().y && mouse.getPosition().y <= m_expeditionsDisplay[i].GetExpeditionBox().getPosition().y + (m_expeditionsDisplay[i].GetExpeditionBox().getSize().y)
			&& !MouseIsOnAnyDiscardPile())
			return true;
	return false;
}

bool BoardDisplay::MouseIsOnAnyDiscardPile()
{
	sf::Mouse mouse;
	for (int i = 0; i < m_expeditionsDisplay.size(); i++)
		if (mouse.getPosition().x >= m_expeditionsDisplay[i].GetDiscardBox().getPosition().x && mouse.getPosition().x <= m_expeditionsDisplay[i].GetDiscardBox().getPosition().x + (m_expeditionsDisplay[i].GetDiscardBox().getSize().x)
			&& mouse.getPosition().y >= m_expeditionsDisplay[i].GetDiscardBox().getPosition().y && mouse.getPosition().y <= m_expeditionsDisplay[i].GetDiscardBox().getPosition().y + (m_expeditionsDisplay[i].GetDiscardBox().getSize().y))
			return true;
	return false;
}

bool BoardDisplay::MouseIsOnACertainDiscardPile(uint16_t cardColorIndex)
{
	sf::Mouse mouse;
	if (mouse.getPosition().x >= m_expeditionsDisplay[cardColorIndex].GetDiscardBox().getPosition().x && mouse.getPosition().y >= m_expeditionsDisplay[cardColorIndex].GetDiscardBox().getPosition().y
		&& (mouse.getPosition().x <= m_expeditionsDisplay[cardColorIndex].GetDiscardBox().getPosition().x + m_expeditionsDisplay[cardColorIndex].GetDiscardBox().getSize().x)
		&& (mouse.getPosition().y <= m_expeditionsDisplay[cardColorIndex].GetDiscardBox().getPosition().y + m_expeditionsDisplay[cardColorIndex].GetDiscardBox().getSize().y))
		return true;
	return false;
}

bool BoardDisplay::MouseIsOnACertainExpedition(uint16_t cardColorIndex)
{
	sf::Mouse mouse;
	if (mouse.getPosition().x >= m_expeditionsDisplay[cardColorIndex].GetExpeditionBox().getPosition().x && mouse.getPosition().y >= m_expeditionsDisplay[cardColorIndex].GetExpeditionBox().getPosition().y
		&& (mouse.getPosition().x <= m_expeditionsDisplay[cardColorIndex].GetExpeditionBox().getPosition().x + m_expeditionsDisplay[cardColorIndex].GetExpeditionBox().getSize().x)
		&& (mouse.getPosition().y <= m_expeditionsDisplay[cardColorIndex].GetExpeditionBox().getPosition().y + m_expeditionsDisplay[cardColorIndex].GetExpeditionBox().getSize().y) 
		&& !MouseIsOnACertainDiscardPile(cardColorIndex))
		return true;
	return false;
}

int BoardDisplay::SelectDiscPile()
{
	sf::Mouse mouse;
	sf::Vector2i position(mouse.getPosition().x, mouse.getPosition().y);
	for (int i = 0; i < 5; i++)
	{
		if (!m_expeditionsDisplay[i].GetDiscardPile().empty() && m_expeditionsDisplay[i].GetDiscardPile().top().MouseIsOnCard())
		{
			m_expeditionsDisplay[i].GetDiscardBox().setOutlineThickness(0.5f);
			return i;
		}
	}
	throw(std::out_of_range("The discard pile is empty.Please select another discard pile to draw from or select the drawing deck!"));
}

void BoardDisplay::SetNumberOfCardsInDeck(int number)
{
	m_numberOfCardsInDeck.setString(std::to_string(number));
}
sf::RectangleShape* BoardDisplay::GetBottomBar()
{
	return m_bottomBar;
}
sf::RectangleShape* BoardDisplay::GetTopBar()
{
	return m_topBar;
}
sf::RectangleShape* BoardDisplay::GetDrawingDeckShape()
{
	return m_drawingDeckShape;
}
std::stack<CardRender>& BoardDisplay::GetDrawingDeck()
{
	return m_drawingDeck;
}
sf::Text BoardDisplay::GetNumberOfCardsInDeck()
{
	return m_numberOfCardsInDeck;
}

void BoardDisplay::GenerateDrawingDeckTexture(sf::RenderWindow& window)
{
	m_drawingDeckShape = new sf::RectangleShape(sf::Vector2f(54, 54));
	m_drawingDeckShape->setPosition(sf::Vector2f(window.getSize().x- m_drawingDeckShape->getSize().x-30,window.getPosition().y+30));
	m_DrawingDeckTexture.loadFromFile("DrawingDeck.jpg");
	m_drawingDeckShape->setTexture(&m_DrawingDeckTexture);

}
void BoardDisplay::GenerateExpeditions(sf::RenderWindow& window)
{
	GenerateTopBar(window);
	GenerateBottomBar(window);
	std::ifstream expTextures("ExpeditionTextures.txt");
	std::ifstream discTextures("DiscardPileTextures.txt");
	std::string eTexture;
	std::string dpTexture;
	for (int exp = 0; exp < m_expeditionsDisplay.size(); exp++)
	{
		expTextures >> eTexture;
		discTextures >> dpTexture;
		m_expeditionsDisplay[exp].SetExpBox(window.getSize().x / 5.f * exp,m_topBar->getSize().y, window.getSize().x / 5, window.getSize().y - 0.2 * window.getSize().y, eTexture);
		m_expeditionsDisplay[exp].SetDiscardBox(60, 60, dpTexture);
	}
}

void BoardDisplay::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < 5; i++)
	{
		m_expeditionsDisplay[i].Draw(window);
	}
	window.draw(*m_topBar);
	window.draw(*m_drawingDeckShape);
	window.draw(m_numberOfCardsInDeck);
	window.draw(*m_bottomBar);
}


std::array<ExpeditionRender, 5>& BoardDisplay::GetExpeditions()
{
	return m_expeditionsDisplay;
}

void BoardDisplay::DrawScoreBoxes(sf::RenderWindow& window)
{
	for (int i = 0; i < m_expeditionsDisplay.size(); ++i)
	{
		window.draw(m_expeditionsDisplay[i].GetExpeditionScoreBox1());
		window.draw(m_expeditionsDisplay[i].GetExpeditionScoreBox2());
	}
}
