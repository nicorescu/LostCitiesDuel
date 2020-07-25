#include "WinState.h"

WinState::WinState(sf::RenderWindow& window, std::stack<State*>* states):State(window, states)
{
	if (!m_font.loadFromFile("Cardinal.ttf"))
	{
		return;
	}
	texture.loadFromFile("WinState.jpg");
	m_background.setSize(sf::Vector2f(m_window->getSize().x, m_window->getSize().y));
	m_background.setTexture(&texture);
	InitializeButtons(m_font);
}

void WinState::InitializeButtons(sf::Font& font)
{
	std::string mainMenu = "Main Menu";
	

	sf::Color idleColor(sf::Color::White);
	sf::Color hoverColor(sf::Color::Yellow);
	sf::Color activeColor(sf::Color::Red);

	m_mainMenuButton.SetButtonAttributes((uint16_t)(m_window->getSize().x / 2 - m_mainMenuButton.GetText().getGlobalBounds().width/2), (uint16_t)(m_window->getSize().y / 2), font, mainMenu, idleColor, hoverColor, activeColor);
}

void WinState::Draw()
{
	sf::Text text;
	text.setFont(m_font);
	text.setString("Game Over");
	text.setCharacterSize(90);
	text.setPosition(m_window->getSize().x / 2 - text.getGlobalBounds().width/2, m_window->getSize().y / 8);
	text.setFillColor(sf::Color::White);
	text.setOutlineThickness(5.f);

	m_window->draw(m_background);
	m_mainMenuButton.Render(*m_window);
	m_window->draw(text);
}

void WinState::Render(sf::RenderTarget& target)
{
	Draw();
}

void WinState::UpdateEvents(sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::MouseMoved:
	{
		if (m_mainMenuButton.MouseIsOnButton())
		{
			m_mainMenuButton.GetText().setFillColor(m_mainMenuButton.GetHoverColor());
		}
		else
			m_mainMenuButton.GetText().setFillColor(m_mainMenuButton.GetIdleColor());
		break;
	}
		case sf::Event::MouseButtonReleased:
	{
		if (m_mainMenuButton.MouseIsOnButton())
		{
			m_mainMenuButton.GetText().setFillColor(m_mainMenuButton.GetHoverColor());
			while (m_states->size() != 1)
				m_states->pop();
		}
		break;
	}
		case sf::Event::MouseButtonPressed:
		{
			if (m_mainMenuButton.MouseIsOnButton())
			{
				m_mainMenuButton.GetText().setFillColor(m_mainMenuButton.GetActiveColor());
			}
			else
				m_mainMenuButton.GetText().setFillColor(m_mainMenuButton.GetIdleColor());
			break;
		}
	}
}
