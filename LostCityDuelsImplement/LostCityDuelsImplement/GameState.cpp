#include "GameState.h"
#include "PauseState.h"
#include "WinState.h"
static void sleepcp(int miliseconds)
{
	clock_t timeEnd;
	timeEnd = clock() + miliseconds * CLOCKS_PER_SEC / 1000;
	while (clock() < timeEnd)
	{
	}
}
GameState::GameState(sf::RenderWindow& window, std::stack <State*>* states) : State(window, states)
{
	if (!m_font.loadFromFile("arial.ttf"))
	{
		return;
	}
	if (!m_roundFont.loadFromFile("Cardinal.ttf"))
	{
		return;
	}
	Initialise();
}
void GameState::Initialise()
{
	m_player1.SetName("Player 1");
	m_player2.SetName("Player 2");
	m_board.GenerateDrawingDeck();
	m_board.GeneratePlayerHand(m_player1);
	m_board.GeneratePlayerHand(m_player2);
	m_boardDisplay.GenerateExpeditions(*m_window);
	m_boardDisplay.GenerateDrawingDeckTexture(*m_window);

	for (int i = 0; i < m_boardDisplay.GetExpeditions().size(); i++)
	{
		m_boardDisplay.GetExpeditions()[i].SetExpeditionScoreBox1(m_boardDisplay.GetExpeditions()[i].GetDiscardBox().getPosition().x - 3 * m_boardDisplay.GetExpeditions()[i].GetDiscardBox().getSize().x, m_boardDisplay.GetExpeditions()[i].GetDiscardBox().getPosition().y);
	}

	for (int i = 0; i < m_boardDisplay.GetExpeditions().size(); i++)
	{
		m_boardDisplay.GetExpeditions()[i].SetExpeditionScoreBox2(m_boardDisplay.GetExpeditions()[i].GetExpeditionScoreBox1().getPosition().x, m_boardDisplay.GetExpeditions()[i].GetExpeditionScoreBox1().getPosition().y + m_boardDisplay.GetExpeditions()[i].GetExpeditionScoreBox1().getSize().y);
	}

	for (int i = 0; i < m_boardDisplay.GetExpeditions().size(); i++)
	{
		m_playerRender1.DrawExpeditionScores(m_font, m_player1, m_boardDisplay.GetExpeditions()[i].GetExpeditionScoreBox1().getPosition().x + m_boardDisplay.GetExpeditions()[i].GetExpeditionScoreBox1().getSize().x / 2, m_boardDisplay.GetExpeditions()[i].GetExpeditionScoreBox1().getPosition().y, i);
		m_playerRender2.DrawExpeditionScores(m_font, m_player2, m_boardDisplay.GetExpeditions()[i].GetExpeditionScoreBox2().getPosition().x + m_boardDisplay.GetExpeditions()[i].GetExpeditionScoreBox2().getSize().x / 2, m_boardDisplay.GetExpeditions()[i].GetExpeditionScoreBox2().getPosition().y, i);
	}

	m_boardDisplay.GenerateNumberOfCardsInDeck(m_font, m_board.GetDrawingDeck().size(), m_window->getSize().x - m_boardDisplay.GetDrawingDeckShape()->getSize().x - 59, m_boardDisplay.GetDrawingDeckShape()->getSize().y / 3 + 30);

	m_playerRender1.SetNameAttributes(m_font, m_player1, m_window->getPosition().x, m_window->getPosition().y);
	m_playerRender1.SetScoreAttributes(m_font, m_player1, m_playerRender1.GetName().getPosition().x + m_playerRender1.GetName().getCharacterSize(), 1.5 * ((int)m_playerRender1.GetName().getPosition().y + m_playerRender1.GetName().getCharacterSize()));
	m_playerRender1.SetPlayerHandAttributes(m_player1, *m_window, m_font, m_window->getPosition().y + m_boardDisplay.GetTopBar()->getSize().y / 3);


	m_playerRender2.SetNameAttributes(m_font, m_player2, m_boardDisplay.GetBottomBar()->getPosition().x, m_boardDisplay.GetBottomBar()->getPosition().y);
	m_playerRender2.SetScoreAttributes(m_font, m_player2, m_playerRender2.GetName().getPosition().x + m_playerRender2.GetName().getCharacterSize(), m_playerRender2.GetName().getPosition().y + 1.5 * (m_playerRender2.GetName().getCharacterSize()));
	m_playerRender2.SetPlayerHandAttributes(m_player2, *m_window, m_font, m_boardDisplay.GetBottomBar()->getPosition().y + m_boardDisplay.GetBottomBar()->getSize().y / 3);
	m_player1.SetTotalScore();
	m_player2.SetTotalScore();
	if (currentPlayer == 0) {
		m_playerRender2.CoverCards();
		m_playerRender1.ShowCards(m_player1, m_font);
	}
	else
	{
		m_playerRender1.CoverCards();
		m_playerRender2.ShowCards(m_player2, m_font);
	}

}

void GameState::UpdateGame()
{

	m_boardDisplay.Draw(*m_window);
	m_window->draw(m_playerRender1.GetName());
	m_window->draw(m_playerRender1.GetScore());
	m_window->draw(m_playerRender2.GetName());
	m_window->draw(m_playerRender2.GetScore());
	m_playerRender1.DrawPlayerHand(*m_window);
	m_playerRender2.DrawPlayerHand(*m_window);
	m_boardDisplay.DrawScoreBoxes(*m_window);
	m_playerRender1.DrawScores(*m_window);
	m_playerRender2.DrawScores(*m_window);

	m_boardDisplay.HighlightExpeditionsCard();
}

void GameState::Render(sf::RenderTarget& target)
{
	UpdateGame();
	CheckCurrentGameStage();
}

void GameState::UpdateEvents(sf::Event& event)
{
	if (currentPlayer == 0) {
		m_playerRender2.CoverCards();
		m_playerRender1.ShowCards(m_player1, m_font);
	}
	else
	{
		m_playerRender1.CoverCards();
		m_playerRender2.ShowCards(m_player2, m_font);
	}

	switch (event.type)
	{
	case sf::Event::Closed:
		m_window->close();
		break;
	case sf::Event::MouseButtonReleased:
	{
		if (currentPlayer == 0)
		{
			//selects
			if (m_playerRender1.MouseIsOnAnyCard() && drawingPhase == false)
			{
				cardIndex = m_playerRender1.SelectCard();
				card = m_playerRender1.GetCardsInHand()[cardIndex];
			}
			//discards
			else if (m_boardDisplay.MouseIsOnACertainDiscardPile(card.GetColorIndex()) && drawingPhase == false && cardIndex != -1)
			{

				uint16_t expeditionIndex = card.GetColorIndex();
				drawingPhase = true;
				m_boardDisplay.GetExpeditions()[expeditionIndex].AddToDiscardPile(card);
				Card placeHolder(Card::Colour::none, Card::CardValues::none);
				m_playerRender1.GetCardsInHand()[cardIndex] = CardRender(placeHolder, m_font);
				m_player1.AddCardToDiscardPile(cardIndex, m_board.GetPile(expeditionIndex));
				m_playerRender1.GetCardsInHand().erase(m_playerRender1.GetCardsInHand().begin() + cardIndex);
				cardIndex = -1;
			}
			//plays
			else if (m_boardDisplay.MouseIsOnACertainExpedition(card.GetColorIndex()) && drawingPhase == false && cardIndex != -1)
			{
				drawingPhase = true;
				uint16_t expeditionIndex = 0;
				expeditionIndex = card.GetColorIndex();
				try
				{
					m_player1.AddCardToExpedition(cardIndex);
					m_player1.SetTotalScore();
					m_playerRender1.GetExpeditionScores()[expeditionIndex].setString(std::to_string(m_player1.GetExpeditions()[expeditionIndex].GetScore()));
					m_playerRender1.GetScore().setString(std::to_string(m_player1.GetCurrentScore()));
					m_playerRender1.GetCardsInHand().erase(m_playerRender1.GetCardsInHand().begin() + cardIndex);
					m_boardDisplay.GetExpeditions()[expeditionIndex].SetPlayer1PlayedCardsDisplay(m_player1.GetExpeditions()[expeditionIndex], m_font);
					cardIndex = -1;
				}
				catch (const char* message)
				{
					drawingPhase = false;
				}
			}
			//draws from deck
			else if (m_boardDisplay.MouseIsOnDrawingDeck() && drawingPhase == true)
			{
				m_boardDisplay.GetDrawingDeckShape()->setOutlineThickness(0.0f);
				drawingPhase = false;
				m_playerRender1.DrawCardFromDeck(m_player1, m_board);
				m_playerRender1.ClearHand();
				m_playerRender1.SetPlayerHandAttributes(m_player1, *m_window, m_font, m_window->getPosition().y + m_boardDisplay.GetTopBar()->getSize().y / 3);
				m_boardDisplay.SetNumberOfCardsInDeck(m_board.GetDrawingDeck().size());
				currentPlayer = 1;
			}
			//draws from discard pile
			else if (m_boardDisplay.MouseIsOnAnyDiscardPile() && drawingPhase == true)
			{
				try
				{
					int dpIndex = m_boardDisplay.SelectDiscPile();
					if (!m_board.GetPile(dpIndex).empty())
					{
						drawingPhase = false;
						m_player1.PlaceCardInPlayerHand(m_board.GetPile(dpIndex).top(), 0);
						m_board.GetPile(dpIndex).pop();
						m_boardDisplay.GetExpeditions()[dpIndex].DrawFromDiscardPile();
					}
					m_playerRender1.ClearHand();
					m_playerRender1.SetPlayerHandAttributes(m_player1, *m_window, m_font, m_window->getPosition().y + m_boardDisplay.GetTopBar()->getSize().y / 3);
				}
				catch (const std::out_of_range msg)
				{

				}
				currentPlayer = 1;
			}
		}
		else if (currentPlayer == 1)
		{
			if (m_playerRender2.MouseIsOnAnyCard() && drawingPhase == false)
			{
				cardIndex = m_playerRender2.SelectCard();
				card = m_playerRender2.GetCardsInHand()[cardIndex];
			}
			else if (m_boardDisplay.MouseIsOnACertainDiscardPile(card.GetColorIndex()) && drawingPhase == false && cardIndex != -1)
			{

				uint16_t expeditionIndex = card.GetColorIndex();
				drawingPhase = true;
				m_boardDisplay.GetExpeditions()[expeditionIndex].AddToDiscardPile(card);
				Card placeHolder(Card::Colour::none, Card::CardValues::none);
				m_playerRender2.GetCardsInHand()[cardIndex] = CardRender(placeHolder, m_font);
				m_player2.AddCardToDiscardPile(cardIndex, m_board.GetPile(expeditionIndex));
				m_playerRender2.GetCardsInHand().erase(m_playerRender2.GetCardsInHand().begin() + cardIndex);
				cardIndex = -1;

			}
			else if (m_boardDisplay.MouseIsOnACertainExpedition(card.GetColorIndex()) && drawingPhase == false && cardIndex != -1)
			{
				drawingPhase = true;
				uint16_t expeditionIndex = 0;
				expeditionIndex = card.GetColorIndex();
				try
				{
					m_player2.AddCardToExpedition(cardIndex);
					m_player2.SetTotalScore();
					m_playerRender2.GetExpeditionScores()[expeditionIndex].setString(std::to_string(m_player2.GetExpeditions()[expeditionIndex].GetScore()));
					m_playerRender2.GetScore().setString(std::to_string(m_player2.GetCurrentScore()));
					m_playerRender2.GetCardsInHand().erase(m_playerRender2.GetCardsInHand().begin() + cardIndex);
					m_boardDisplay.GetExpeditions()[expeditionIndex].SetPlayer2PlayedCardsDisplay(m_player2.GetExpeditions()[expeditionIndex], m_font);
					cardIndex = -1;
				}
				catch (const char* message)
				{
					drawingPhase = false;
				}
			}
			else if (m_boardDisplay.MouseIsOnDrawingDeck() && drawingPhase == true)
			{
				m_boardDisplay.GetDrawingDeckShape()->setOutlineThickness(0.0f);
				drawingPhase = false;
				m_playerRender2.DrawCardFromDeck(m_player2, m_board);
				m_playerRender2.ClearHand();
				m_playerRender2.SetPlayerHandAttributes(m_player2, *m_window, m_font, m_boardDisplay.GetBottomBar()->getPosition().y + m_boardDisplay.GetBottomBar()->getSize().y / 3);
				m_boardDisplay.SetNumberOfCardsInDeck(m_board.GetDrawingDeck().size());
				currentPlayer = 0;
			}

			//player 2 draws from discard pile
			else if (m_boardDisplay.MouseIsOnAnyDiscardPile() && drawingPhase == true)
			{
				try
				{
					int dpIndex = m_boardDisplay.SelectDiscPile();
					if (!m_board.GetPile(dpIndex).empty())
					{
						drawingPhase = false;
						m_player2.PlaceCardInPlayerHand(m_board.GetPile(dpIndex).top(), 0);
						m_board.GetPile(dpIndex).pop();
						m_boardDisplay.GetExpeditions()[dpIndex].DrawFromDiscardPile();
					}
					m_playerRender2.ClearHand();
					m_playerRender2.SetPlayerHandAttributes(m_player2, *m_window, m_font, m_boardDisplay.GetBottomBar()->getPosition().y + m_boardDisplay.GetBottomBar()->getSize().y / 3);
				}
				catch (const std::out_of_range msg)
				{

				}
				currentPlayer = 0;
			}
		}

		else if (m_boardDisplay.MouseIsOnDrawingDeck() && drawingPhase == true)
		{
			m_boardDisplay.GetDrawingDeckShape()->setOutlineColor(sf::Color::Black);
			m_boardDisplay.GetDrawingDeckShape()->setOutlineThickness(5.0f);
		}
		break;
	}
	case sf::Event::KeyPressed:
	{
		if (event.key.code == sf::Keyboard::Escape)
			m_states->push(new PauseState(*m_window, m_states));
	}
	default:
		break;
	}
}

void GameState::CheckCurrentGameStage()
{
	if (currentPlayer == 0) {
		m_playerRender2.CoverCards();
		m_playerRender1.ShowCards(m_player1, m_font);
	}
	else
	{
		m_playerRender1.CoverCards();
		m_playerRender2.ShowCards(m_player2, m_font);
	}

	if (m_board.GetDrawingDeck().size() == 0)
		if (currentRound < 3)
		{
			sf::Text text;
			text.setFillColor(sf::Color::Black);
			text.setCharacterSize(150);
			text.setFont(m_roundFont);
			text.setString("Round " + std::to_string(currentRound) + " finished!");
			text.setPosition(m_window->getSize().x / 2 - text.getGlobalBounds().width / 2, m_window->getSize().y / 2 - text.getGlobalBounds().height / 2);
			currentRound++;
			m_board.ResetBoard();
			m_board.GetDrawingDeck().resize(0);
			if (m_player1.GetCurrentScore() > m_player2.GetCurrentScore())
				player1Wins++;
			else if (m_player1.GetCurrentScore() < m_player2.GetCurrentScore())
				player2Wins++;
			else 
				currentRound--;
			m_player1.ResetPlayer();
			m_player2.ResetPlayer();
			m_playerRender1.GetScore().setString("0");
			m_playerRender2.GetScore().setString("0");
			for (int exp = 0; exp < m_boardDisplay.GetExpeditions().size(); exp++)
			{
				m_boardDisplay.GetExpeditions()[exp].ClearExpedition();
				m_playerRender1.GetExpeditionScores()[exp].setString("0");
				m_playerRender2.GetExpeditionScores()[exp].setString("0");
			}
			m_board.GenerateDrawingDeck();
			m_board.GeneratePlayerHand(m_player1);
			m_board.GeneratePlayerHand(m_player2);
			m_boardDisplay.SetNumberOfCardsInDeck(m_board.GetDrawingDeck().size());
			while (m_boardDisplay.GetDrawingDeck().size() > 0)
				m_boardDisplay.GetDrawingDeck().pop();
			m_playerRender1.ClearHand();
			m_playerRender2.ClearHand();
			m_playerRender1.SetPlayerHandAttributes(m_player1, *m_window, m_font, m_window->getPosition().y + m_boardDisplay.GetTopBar()->getSize().y / 3);
			m_playerRender2.SetPlayerHandAttributes(m_player2, *m_window, m_font, m_boardDisplay.GetBottomBar()->getPosition().y + m_boardDisplay.GetBottomBar()->getSize().y / 3);
			m_window->draw(text);
			m_window->display();
			sleepcp(2000);
			currentPlayer = 0;
		}
		else if (currentRound == 3)
		{
			if (m_player1.GetCurrentScore() > m_player2.GetCurrentScore())
				player1Wins++;
			else if (m_player1.GetCurrentScore() < m_player2.GetCurrentScore())
				player2Wins++;
			else
				currentRound--;
			currentRound++;
		}
		else
		{
			if (player1Wins > player2Wins)
			{
				sf::Text text;
				text.setFillColor(sf::Color::Black);
				text.setCharacterSize(150);
				text.setFont(m_roundFont);
				text.setString(m_playerRender1.GetName().getString() + " has won the game!");
				text.setPosition(m_window->getSize().x / 2 - text.getGlobalBounds().width / 2, m_window->getSize().y / 2 - text.getGlobalBounds().height / 2);
				m_window->draw(text);
				m_window->display();
				sleepcp(5000);
				m_states->push(new WinState(*m_window, m_states));
			}
			else if (player2Wins > player1Wins)
			{
				sf::Text text;
				text.setFillColor(sf::Color::Black);
				text.setCharacterSize(150);
				text.setFont(m_roundFont);
				text.setString(m_playerRender2.GetName().getString() + " has won the game!");
				text.setPosition(m_window->getSize().x / 2 - text.getGlobalBounds().width / 2, m_window->getSize().y / 2 - text.getGlobalBounds().height / 2);
				m_window->draw(text);
				m_window->display();
				sleepcp(5000);
				m_states->push(new WinState(*m_window, m_states));
			}
		}
}

