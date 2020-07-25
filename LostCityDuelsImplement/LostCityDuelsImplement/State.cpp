#include "State.h"

State::State(sf::RenderWindow& window, std::stack <State*>* states)
{
	m_window = &window;
	m_states = states;
}
