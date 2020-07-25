#include "Game.h"

Game::Game()
{
	const auto desktopSize = sf::VideoMode::getDesktopMode();
	m_window =new sf::RenderWindow(desktopSize, "Test", sf::Style::Close | sf::Style::Fullscreen);
}

void Game::RunGame()
{
	m_stateStack.push(new MenuState(*m_window, &m_stateStack));
}

void Game::Render()
{
	while (m_window->isOpen())
	{
		while (m_window->pollEvent(m_event))
		{
			if (!m_stateStack.empty())
				m_stateStack.top()->UpdateEvents(m_event);
		}
		m_window->clear();
		if (!m_stateStack.empty())
		{
			m_stateStack.top()->Render(*m_window);
		}
		m_window->display();
	}
}
