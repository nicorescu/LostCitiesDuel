#pragma once
#include "BoardDisplay.h"
#include "State.h"
class GameState : public State
{
public:
	GameState(sf::RenderWindow &window, std::stack <State*>* states);
	void Initialise();
	void UpdateGame();
	void Render(sf::RenderTarget& target) override;
	void UpdateEvents(sf::Event &event) override;
	void CheckCurrentGameStage();

private:
	Player m_player1;
	Player m_player2;
	Board m_board;
private:
	PlayerRender m_playerRender1;
	PlayerRender m_playerRender2;
	BoardDisplay m_boardDisplay;
	CardRender card;
private:
	sf::Font m_font;
	sf::Font m_roundFont;
private:
	int currentRound = 1;
	uint16_t player1Wins = 0;
	uint16_t player2Wins = 0;
	bool drawingPhase = false;
	bool currentPlayer = 0;
	int cardIndex = -1;
};

