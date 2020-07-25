#include "CardRender.h"

CardRender::CardRender()
{
	
}

CardRender::CardRender(const Card& card, sf::Font& font)
{
	
	Card anotherCard(std::move(card));
	SetCardAttributes(anotherCard);
	SetText(anotherCard, font);
}

void CardRender::SetCardAttributes(const Card& card)
{
	
	
	if (card.GetColor() == Card::Colour::gold)
	{
		m_cardDisplay.setFillColor(sf::Color::Yellow);
	}
	else if (card.GetColor() == Card::Colour::blue)
	{
		m_cardDisplay.setFillColor(sf::Color(80,80,255));
	}
	else if (card.GetColor() == Card::Colour::white)
	{
		m_cardDisplay.setFillColor(sf::Color::White);
	}
	else if (card.GetColor() == Card::Colour::green)
	{
		m_cardDisplay.setFillColor(sf::Color::Green);
	}
	else if (card.GetColor() == Card::Colour::red)
	{
		m_cardDisplay.setFillColor(sf::Color::Red);
	}
}

void CardRender::SetCardPosition(float x, float y)
{
	m_cardDisplay.setPosition(x, y);
	if (m_cardSymbol.getString()=="10")
		m_cardSymbol.setPosition(m_cardDisplay.getPosition().x + m_cardDisplay.getSize().x / 6, m_cardDisplay.getPosition().y + m_cardDisplay.getSize().y / 6);
	else
		m_cardSymbol.setPosition(m_cardDisplay.getPosition().x + m_cardDisplay.getSize().x / 3, m_cardDisplay.getPosition().y + m_cardDisplay.getSize().y/6);
}

void CardRender::SetCardSizes(float width, float height)
{
	m_cardDisplay.setSize(sf::Vector2f(width, height));
}

uint16_t CardRender::GetColorIndex() const
{
	uint16_t expeditionIndex{};
	if (m_cardDisplay.getFillColor() == sf::Color::Yellow)
	{
		expeditionIndex = 0;
	}
	else if (m_cardDisplay.getFillColor() == sf::Color(80, 80, 255))
	{
		expeditionIndex = 1;
	}
	else if (m_cardDisplay.getFillColor() == sf::Color::White)
	{
		expeditionIndex = 2;
	}
	else if (m_cardDisplay.getFillColor() == sf::Color::Green)
	{
		expeditionIndex = 3;
	}
	else if (m_cardDisplay.getFillColor() == sf::Color::Red)
	{
		expeditionIndex = 4;
	}
	return expeditionIndex;
}

sf::RectangleShape& CardRender::GetCardDisplay()
{
	return m_cardDisplay;
}

sf::Text& CardRender::GetCardSymbol()
{
	return m_cardSymbol;
}

void CardRender::SetText(const Card& card, sf::Font& font)
{
	m_cardSymbol.setFillColor(sf::Color::Black);
	m_cardSymbol.setFont(font);
	m_cardSymbol.setCharacterSize(31);

	if (card.GetValue() == Card::CardValues::investition)
	{
		m_cardSymbol.setString("$");
	}
	else if (card.GetValue() == Card::CardValues::secondCard)
	{
		m_cardSymbol.setString("2");
	}
	else if (card.GetValue() == Card::CardValues::thirdCard)
	{
		m_cardSymbol.setString("3");
	}
	else if (card.GetValue() == Card::CardValues::fourthCard)
	{
		m_cardSymbol.setString("4");
	}
	else if (card.GetValue() == Card::CardValues::fifthCard)
	{
		m_cardSymbol.setString("5");
	}
	else if (card.GetValue() == Card::CardValues::sixthCard)
	{
		m_cardSymbol.setString("6");
	}
	else if (card.GetValue() == Card::CardValues::seventhCard)
	{
		m_cardSymbol.setString("7");
	}
	else if (card.GetValue() == Card::CardValues::eighthCard)
	{
		m_cardSymbol.setString("8");
	}
	else if (card.GetValue() == Card::CardValues::ninthCard)
	{
		m_cardSymbol.setString("9");
	}
	else if (card.GetValue() == Card::CardValues::tenthCard)
	{
		m_cardSymbol.setString("10");
	}
	
}

bool CardRender::MouseIsOnCard()
{
	sf::Mouse mouse;
	if (mouse.getPosition().x >= m_cardDisplay.getPosition().x && mouse.getPosition().x <= (m_cardDisplay.getPosition().x + m_cardDisplay.getSize().x)
		&& mouse.getPosition().y >= m_cardDisplay.getPosition().y && mouse.getPosition().y <= (m_cardDisplay.getPosition().y + m_cardDisplay.getSize().y))
		return true;
	return false;
}

void CardRender::HighlightCard()
{
	m_cardDisplay.setOutlineThickness(5.f);
	m_cardDisplay.setOutlineColor(sf::Color::Black);
}

void CardRender::Draw(sf::RenderWindow& window)
{
	window.draw(m_cardDisplay);
	window.draw(m_cardSymbol);
}
