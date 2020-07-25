#pragma once
#include<SFML/Graphics.hpp>
#include "Button.h"
#include<stack>
class State
{
public:
	State(sf::RenderWindow& window, std::stack <State*>* states);
	virtual void Render(sf::RenderTarget& target)=0;
	virtual void UpdateEvents(sf::Event& event)=0;
protected:
	sf::RenderWindow* m_window;
	std::stack <State*>* m_states;
};

