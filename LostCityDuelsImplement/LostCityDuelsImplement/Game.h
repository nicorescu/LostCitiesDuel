#pragma once
#include "MenuState.h"
class Game
{
public:
	Game();
	void RunGame();
	void Render();
private:
	std::stack <State*> m_stateStack;
	sf::RenderWindow* m_window;
	sf::Event m_event;
};

