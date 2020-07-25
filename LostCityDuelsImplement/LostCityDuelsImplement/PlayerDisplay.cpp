#include "PlayerDisplay.h"

std::vector<sf::RectangleShape> PlayerDisplay::GetCardsInHand()
{
	return m_cardsInHand;
}

sf::Text PlayerDisplay::GetPlayerNameDisplayed()
{
	return m_playerNameDisplayed;
}

void PlayerDisplay::SetPlayerNameDisplayed(sf::Text& name)
{
	m_playerNameDisplayed = name;
}

void PlayerDisplay::DisplayHand(Player& currentPlayingPlayer,BoardDisplay& board)
{
	for (int i = 0; i < currentPlayingPlayer.GetPlayerHand().size(); i++)
	{
		sf::RectangleShape card(sf::Vector2f((board.GetWindow()->getSize().y / 15.f), board.GetWindow()->getSize().y / 15.f));
		card.setPosition((board.GetWindow()->getSize().x / 8.f) * (i + 0.3f), board.GetWindow()->getSize().y - board.GetWindow()->getSize().y / 10.f);
		if (currentPlayingPlayer.GetPlayerHand()[i].GetColor() == Card::Colour::gold)
		{
			card.setFillColor(sf::Color::Yellow);
		}
		else if (currentPlayingPlayer.GetPlayerHand()[i].GetColor() == Card::Colour::blue)
		{
			card.setFillColor(sf::Color::Blue);
		}
		else if (currentPlayingPlayer.GetPlayerHand()[i].GetColor() == Card::Colour::white)
		{
			card.setFillColor(sf::Color::White);
		}
		else if (currentPlayingPlayer.GetPlayerHand()[i].GetColor() == Card::Colour::green)
		{
			card.setFillColor(sf::Color::Green);
		}
		else if (currentPlayingPlayer.GetPlayerHand()[i].GetColor() == Card::Colour::red)
		{
			card.setFillColor(sf::Color::Red);
		}
		m_cardsInHand.push_back(card);
	}
	for (int i = 0; i < 8; i++)
	{
		sf::Font font;
		sf::Text text;
		if (!font.loadFromFile("arial.ttf"))
			break;
		text.setFont(font);
		text.setCharacterSize(31);

		if (currentPlayingPlayer.GetPlayerHand()[i].GetValue() == Card::CardValues::investition)
		{
			text.setString("$");
		}
		else if (currentPlayingPlayer.GetPlayerHand()[i].GetValue() == Card::CardValues::secondCard)
		{
			text.setString("2");
		}
		else if (currentPlayingPlayer.GetPlayerHand()[i].GetValue() == Card::CardValues::thirdCard)
		{
			text.setString("3");
		}
		else if (currentPlayingPlayer.GetPlayerHand()[i].GetValue() == Card::CardValues::fourthCard)
		{
			text.setString("4");
		}
		else if (currentPlayingPlayer.GetPlayerHand()[i].GetValue() == Card::CardValues::fifthCard)
		{
			text.setString("5");
		}
		else if (currentPlayingPlayer.GetPlayerHand()[i].GetValue() == Card::CardValues::sixthCard)
		{
			text.setString("6");
		}
		else if (currentPlayingPlayer.GetPlayerHand()[i].GetValue() == Card::CardValues::seventhCard)
		{
			text.setString("7");
		}
		else if (currentPlayingPlayer.GetPlayerHand()[i].GetValue() == Card::CardValues::eighthCard)
		{
			text.setString("8");
		}
		else if (currentPlayingPlayer.GetPlayerHand()[i].GetValue() == Card::CardValues::ninthCard)
		{
			text.setString("9");
		}
		else if (currentPlayingPlayer.GetPlayerHand()[i].GetValue() == Card::CardValues::tenthCard)
		{
			text.setString("10");
		}

		text.setPosition(m_cardsInHand[i].getPosition().x + m_cardsInHand[i].getSize().x / 2, m_cardsInHand[i].getPosition().y + m_cardsInHand[i].getSize().y / 2);
		text.setFillColor(sf::Color(0, 0, 0, 255));
		m_cardsNumber.push_back(text);
		board.GetWindow()->draw(m_cardsInHand[i]);
		board.GetWindow()->draw(text);
	}

}



