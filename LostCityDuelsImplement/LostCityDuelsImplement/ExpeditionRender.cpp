#include "ExpeditionRender.h"

void ExpeditionRender::SetPlayer2PlayedCardsDisplay(Expedition chosenExpedition, sf::Font &font)
{
	int cardSpacing = 0;
	float ySpacing = 0;
	for (int i = 0; i < chosenExpedition.GetPlayedCards().size(); i++)
	{
		CardRender myRenderedCard;
		myRenderedCard.SetCardAttributes(chosenExpedition.GetPlayedCards()[i]);
		myRenderedCard.SetCardSizes(50, 50);
		myRenderedCard.SetText(chosenExpedition.GetPlayedCards()[i], font);
		myRenderedCard.SetCardPosition(m_expeditionBox.getPosition().x + (m_expeditionBox.getSize().x/6.f) * cardSpacing, m_expeditionBox.getSize().y -5 * (myRenderedCard.GetCardDisplay().getSize().y) + ySpacing * (myRenderedCard.GetCardDisplay().getSize().y));
		if (myRenderedCard.GetCardDisplay().getPosition().x+myRenderedCard.GetCardDisplay().getSize().x > (m_expeditionBox.getPosition().x+m_expeditionBox.getSize().x))
		{
			ySpacing = 1.5;
			cardSpacing = 0;
			int newX = m_expeditionBox.getPosition().x + (m_expeditionBox.getSize().x / 6.f) * cardSpacing;
			int newY = (m_expeditionBox.getSize().y - 5 * (myRenderedCard.GetCardDisplay().getSize().y)) + ySpacing*(myRenderedCard.GetCardDisplay().getSize().y);
			myRenderedCard.SetCardPosition(newX, newY);
		}
		m_playedCardsDisplay.push_back(myRenderedCard);
		++cardSpacing;
	}
}

void ExpeditionRender::SetPlayer1PlayedCardsDisplay(Expedition chosenExpedition, sf::Font& font)
{
	int cardSpacing = 0;
	float ySpacing = 0;
	for (int i = 0; i < chosenExpedition.GetPlayedCards().size(); i++)
	{
		CardRender myRenderedCard;
		myRenderedCard.SetCardAttributes(chosenExpedition.GetPlayedCards()[i]);
		myRenderedCard.SetCardSizes(50, 50);
		myRenderedCard.SetText(chosenExpedition.GetPlayedCards()[i], font);
		myRenderedCard.SetCardPosition(m_expeditionBox.getPosition().x + (m_expeditionBox.getSize().x / 6.f) * cardSpacing, m_expeditionBox.getPosition().y + 6 * (myRenderedCard.GetCardDisplay().getSize().y) + ySpacing * (myRenderedCard.GetCardDisplay().getSize().y));
		if (myRenderedCard.GetCardDisplay().getPosition().x + myRenderedCard.GetCardDisplay().getSize().x > (m_expeditionBox.getPosition().x + m_expeditionBox.getSize().x))
		{
			ySpacing = 1.5;
			cardSpacing = 0;
			int newX = m_expeditionBox.getPosition().x + (m_expeditionBox.getSize().x / 6.f) * cardSpacing;
			int newY = (m_expeditionBox.getPosition().y + 2 * (myRenderedCard.GetCardDisplay().getSize().y)) + ySpacing * (myRenderedCard.GetCardDisplay().getSize().y);
			myRenderedCard.SetCardPosition(newX, newY);
		}
		m_playedCardsDisplay.push_back(myRenderedCard);
		++cardSpacing;
	}
}

void ExpeditionRender::SetExpBox(float x, float y, float width, float height, std::string chosenTexture)
{
	m_background.loadFromFile(chosenTexture);
	m_background.setSmooth(true);
	m_expeditionBox.setSize(sf::Vector2f(width, height));
	m_expeditionBox.setTexture(&m_background);
	m_expeditionBox.setPosition(x, y);
}

void ExpeditionRender::SetDiscardBox(float width, float height, std::string chosenTexture)
{
	m_pileTexture.loadFromFile(chosenTexture);
	m_pileTexture.setSmooth(true);
	m_discardPileBox.setSize(sf::Vector2f(width, height));
	m_discardPileBox.setTexture(&m_pileTexture);
	m_discardPileBox.setPosition(m_expeditionBox.getPosition().x + m_expeditionBox.getSize().x/2.0f, m_expeditionBox.getPosition().y + m_expeditionBox.getSize().y / 2.0f);

}

void ExpeditionRender::AddToDiscardPile(CardRender& playerCard)
{
	playerCard.SetCardSizes(50, 50);
	playerCard.GetCardDisplay().setOutlineThickness(0.f);
	playerCard.SetCardPosition(m_discardPileBox.getPosition().x + 5, m_discardPileBox.getPosition().y + 5);
	m_discardPileDisplay.push(playerCard);
}

void ExpeditionRender::DrawFromDiscardPile()
{
	if (!m_discardPileDisplay.empty())
		m_discardPileDisplay.pop();
	else throw std::out_of_range("Discard pile is empty.");
}

void ExpeditionRender::Draw(sf::RenderWindow& window)
{
	window.draw(m_expeditionBox);
	window.draw(m_discardPileBox);
	window.draw(m_expeditionScoreBox1);
	for (int index = 0; index < m_playedCardsDisplay.size(); index++)
	{
		m_playedCardsDisplay[index].Draw(window);
	}
	if(!m_discardPileDisplay.empty())
		m_discardPileDisplay.top().Draw(window);
}

void ExpeditionRender::HighlightExpeditionCard()
{
	for (int i = 0; i < m_playedCardsDisplay.size(); i++)
		if (IsMouseOnExpeditionCard(m_playedCardsDisplay[i]))
		{
			m_playedCardsDisplay[i].GetCardDisplay().setOutlineThickness(5.f);
			m_playedCardsDisplay[i].GetCardDisplay().setOutlineColor(sf::Color::Black);
		}
		else
		{
			m_playedCardsDisplay[i].GetCardDisplay().setOutlineThickness(0.f);
		}
}

bool ExpeditionRender::IsMouseOnExpeditionCard(CardRender card)
{
	sf::Mouse mouse;
	if (mouse.getPosition().x >= card.GetCardDisplay().getPosition().x && mouse.getPosition().x <= (card.GetCardDisplay().getPosition().x + card.GetCardDisplay().getSize().x)
		&& mouse.getPosition().y >= card.GetCardDisplay().getPosition().y && mouse.getPosition().y <= (card.GetCardDisplay().getPosition().y + card.GetCardDisplay().getSize().y))
		return true;
	return false;
}

void ExpeditionRender::DrawCardOnDiscard(CardRender card, sf::RenderWindow& window)
{
	card.SetCardSizes(50, 50);
	card.SetCardPosition(m_expeditionBox.getPosition().x, m_expeditionBox.getPosition().y);
	card.Draw(window);
}

bool ExpeditionRender::MouseIsOnDiscardPile()
{
	sf::Mouse mouse;
	if (mouse.getPosition().x >=m_discardPileBox.getPosition().x && mouse.getPosition().x <= m_discardPileBox.getPosition().x + (m_discardPileBox.getSize().x)
		&& mouse.getPosition().y >= m_discardPileBox.getPosition().y && mouse.getPosition().y <= m_discardPileBox.getPosition().y + (m_discardPileBox.getSize().y))
		return true;
	return false;
}

sf::RectangleShape& ExpeditionRender::GetDiscardBox()
{
	return m_discardPileBox;
}

sf::RectangleShape ExpeditionRender::GetExpeditionBox()
{
	return m_expeditionBox;
}

std::vector<CardRender>& ExpeditionRender::GetPlayedCards()
{
	return m_playedCardsDisplay;
}

std::stack<CardRender>& ExpeditionRender::GetDiscardPile()
{
	return m_discardPileDisplay;
}

uint16_t ExpeditionRender::GetColorIndex()
{
	if (m_expeditionBox.getOutlineColor() == sf::Color::Yellow)
		return 0;
	if (m_expeditionBox.getOutlineColor() == sf::Color::Blue)
		return 1;
	if (m_expeditionBox.getOutlineColor() == sf::Color::White)
		return 2;
	if (m_expeditionBox.getOutlineColor() == sf::Color::Green)
		return 3;
	if (m_expeditionBox.getOutlineColor() == sf::Color::Red)
		return 4;
}

void ExpeditionRender::SetExpeditionScoreBox2(float x, float y)
{
	m_scoreBoxTexture.loadFromFile("expeditionBox.jpg");
	m_expeditionScoreBox2.setSize(sf::Vector2f(2 * m_discardPileBox.getSize().x, m_discardPileBox.getSize().y / 2));
	m_expeditionScoreBox2.setPosition(x, y);
	m_expeditionScoreBox2.setTexture(&m_scoreBoxTexture);
	m_expeditionScoreBox2.setFillColor(sf::Color(255, 255, 255, 150));
}

void ExpeditionRender::ClearExpedition()
{
	while (m_playedCardsDisplay.size() > 0)
		m_playedCardsDisplay.pop_back();
	while (m_discardPileDisplay.size() > 0)
		m_discardPileDisplay.pop();

}

sf::RectangleShape ExpeditionRender::GetExpeditionScoreBox2()
{
	return m_expeditionScoreBox2;
}

void ExpeditionRender::SetExpeditionScoreBox1(float x, float y)
{
	m_scoreBoxTexture.loadFromFile("expeditionBox.jpg");
	m_expeditionScoreBox1.setSize(sf::Vector2f(2 * m_discardPileBox.getSize().x, m_discardPileBox.getSize().y/2));
	m_expeditionScoreBox1.setPosition(x, y);
	m_expeditionScoreBox1.setTexture(&m_scoreBoxTexture);
	m_expeditionScoreBox1.setFillColor(sf::Color(255, 255, 255, 100));
}

sf::RectangleShape ExpeditionRender::GetExpeditionScoreBox1()
{
	return m_expeditionScoreBox1;
}
