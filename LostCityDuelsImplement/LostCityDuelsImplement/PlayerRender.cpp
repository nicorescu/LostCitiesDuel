#include "PlayerRender.h"

void PlayerRender::ClearHand()
{
	while (m_cardsInHand.size() > 0)
		m_cardsInHand.pop_back();
}

void PlayerRender::SetNameAttributes(sf::Font& font, Player& chosenPlayer, float x, float y)
{
	m_playerNameDisplayed.setFont(font);
	m_playerNameDisplayed.setCharacterSize(31);
	m_playerNameDisplayed.setString(chosenPlayer.GetPlayerName());
	m_playerNameDisplayed.setPosition(x, y);
}

sf::Text PlayerRender::GetName()
{
	return m_playerNameDisplayed;
}

void PlayerRender::SetScoreAttributes(sf::Font& font, Player& chosenPlayer, float x, float y)
{
	m_playerScore.setFont(font);
	m_playerScore.setCharacterSize(25);
	m_playerScore.setString(std::to_string(chosenPlayer.GetCurrentScore()));
	m_playerScore.setPosition(x, y);
}

sf::Text& PlayerRender::GetScore()
{
	return m_playerScore;
}

void PlayerRender::SetPlayerHandAttributes(Player& currentPlayer,sf::RenderWindow &window, sf::Font& font,float y)
{
	CardRender firstCard;
	m_hideHandTexture.loadFromFile("HandBackground.jpg");
	firstCard.SetCardAttributes(currentPlayer.GetPlayerHand()[0]);
	firstCard.SetCardSizes(50, 50);
	firstCard.SetText(currentPlayer.GetPlayerHand()[0], font);
	firstCard.SetCardPosition((window.getSize().x / 5) , y);
	m_cardsInHand.push_back(firstCard);
	for (int i = 1; i < currentPlayer.GetPlayerHand().size(); i++)
	{
		CardRender card;
		card.SetCardAttributes(currentPlayer.GetPlayerHand()[i]);
		card.SetCardSizes(50, 50);
		card.SetText(currentPlayer.GetPlayerHand()[i], font);
		card.SetCardPosition((firstCard.GetCardDisplay().getPosition().x)+(3*(firstCard.GetCardDisplay().getSize()).x), y);
		firstCard = card;
		m_cardsInHand.push_back(card);
	}
}


std::vector<CardRender>& PlayerRender::GetCardsInHand()
{
	return m_cardsInHand;
}

std::vector<sf::Text>& PlayerRender::GetExpeditionScores()
{
	return m_scorePerExpedition;
}

void PlayerRender::DrawExpeditionScores(sf::Font& font, Player& chosenPlayer, float x, float y,int index)
{
	sf::Text score;
	score.setFont(font);
	score.setCharacterSize(25);
	score.setString(std::to_string(chosenPlayer.GetExpeditions()[index].GetScore()));
	score.setPosition(x, y);
	m_scorePerExpedition.push_back(score);
}

void PlayerRender::DrawPlayerHand(sf::RenderWindow& window)
{
	for (int i = 0; i < m_cardsInHand.size(); i++)
	{
		window.draw(m_cardsInHand[i].GetCardDisplay());
		window.draw(m_cardsInHand[i].GetCardSymbol());
	}
}

void PlayerRender::DrawScores(sf::RenderWindow& window)
{
	for (int i = 0; i < m_scorePerExpedition.size(); ++i)
	{
		window.draw(m_scorePerExpedition[i]);
	}
}

int PlayerRender::SelectCard()
{
	for(int i=0;i<m_cardsInHand.size();i++)
		m_cardsInHand[i].GetCardDisplay().setOutlineThickness(0.f);
	for (int i = 0; i < m_cardsInHand.size(); i++)
	{	
		
		if (m_cardsInHand[i].MouseIsOnCard())
		{
			m_cardsInHand[i].HighlightCard();
			return i;
		}
	}
}

bool PlayerRender::MouseIsOnAnyCard()
{
	sf::Mouse mouse;
	for(int i=0; i<m_cardsInHand.size(); i++)
	if (mouse.getPosition().x >= m_cardsInHand[i].GetCardDisplay().getPosition().x && mouse.getPosition().x <= (m_cardsInHand[i].GetCardDisplay().getPosition().x + m_cardsInHand[i].GetCardDisplay().getSize().x)
		&& mouse.getPosition().y >= m_cardsInHand[i].GetCardDisplay().getPosition().y && mouse.getPosition().y <= (m_cardsInHand[i].GetCardDisplay().getPosition().y + m_cardsInHand[i].GetCardDisplay().getSize().y))
		return true;
	return false;
}

void PlayerRender::HighlightChosenCardForAWhile()
{
	for (int i = 0; i < m_cardsInHand.size(); i++)
		m_cardsInHand[i].GetCardDisplay().setOutlineThickness(0.f);
	for(int i=0; i<m_cardsInHand.size(); i++)
		if (m_cardsInHand[i].MouseIsOnCard())
		{
			m_cardsInHand[i].GetCardDisplay().setOutlineThickness(5.f);
			m_cardsInHand[i].GetCardDisplay().setOutlineColor(sf::Color::Black);
		}
}

void PlayerRender::DrawCardFromDeck(Player& player, Board& board)
{
	if (!board.GetDrawingDeck().empty() && (m_cardsInHand.size() < 8 && !m_cardsInHand.empty()))
	{
		Card card = board.ExtractCardFromDeck();
		player.PlaceCardInPlayerHand(card, 0);
	}
}

void PlayerRender::CoverCards()
{

	for (int i = 0; i < m_cardsInHand.size(); i++)
	{
		m_cardsInHand[i].GetCardDisplay().setTexture(&m_hideHandTexture);
		m_cardsInHand[i].GetCardDisplay().setFillColor(sf::Color(0, 0, 0, 0));
		m_cardsInHand[i].GetCardSymbol().setString("");
	}
}

void PlayerRender::ShowCards(Player& currentPlayer, sf::Font& font)
{
	
	for (int i = 0; i < currentPlayer.GetPlayerHand().size(); i++)
	{

		m_cardsInHand[i].SetText(currentPlayer.GetPlayerHand()[i], font);
		m_cardsInHand[i].SetCardAttributes(currentPlayer.GetPlayerHand()[i]);
		m_cardsInHand[i].GetCardDisplay().setTexture(NULL);

	}
}




