#include "MenuState.h"
#include "RulesState.h"
#include "GameState.h"

MenuState::MenuState(sf::RenderWindow &window, std::stack <State*>* states) : State(window, states)
{
	if (!m_font.loadFromFile("Cardinal.ttf"))
	{
		return;
	}
	texture.loadFromFile("Cover.jpg");
	m_background.setSize(sf::Vector2f(m_window->getSize().x, m_window->getSize().y));
	m_background.setTexture(&texture);
	InitializeButtons(m_font);
}

void MenuState::InitializeButtons(sf::Font& font)
{
	std::string play = "PLAY";
	std::string rules = "RULES";
	std::string exit = "EXIT";

	sf::Color idleColor(sf::Color::White);
	sf::Color hoverColor(sf::Color::Yellow);
	sf::Color activeColor(sf::Color::Red);

	m_playButton.SetButtonAttributes((uint16_t)(m_window->getSize().x / 2 - m_playButton.GetText().getGlobalBounds().width/2), (uint16_t)(m_window->getSize().y / (number_of_buttons + 1) * 1+400), font, play, idleColor, hoverColor, activeColor);
	m_rulesButton.SetButtonAttributes((uint16_t)(m_window->getSize().x / 2 - m_rulesButton.GetText().getGlobalBounds().width/2), (uint16_t)(m_window->getSize().y / (number_of_buttons + 1) * 1.5+400), font, rules, idleColor, hoverColor, activeColor);
	m_exitButton.SetButtonAttributes((uint16_t)(m_window->getSize().x / 2 - m_exitButton.GetText().getGlobalBounds().width/2), (uint16_t)(m_window->getSize().y / (number_of_buttons + 1) * 2+400), font, exit, idleColor, hoverColor, activeColor);
}

void MenuState::Draw()
{
	/*target.draw(m_playButton.GetText());
	target.draw(m_rulesButton.GetText());
	target.draw(m_exitButton.GetText());*/
	m_window->draw(m_background);
	m_playButton.Render(*m_window);
	m_rulesButton.Render(*m_window);
	m_exitButton.Render(*m_window);
	

}

void MenuState::Render(sf::RenderTarget& target)
{
	Draw();
}

void MenuState::UpdateEvents(sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::MouseMoved:
	{
		if (m_rulesButton.MouseIsOnButton())
			m_rulesButton.GetText().setFillColor(m_rulesButton.GetHoverColor());
		else
			m_rulesButton.GetText().setFillColor(m_rulesButton.GetIdleColor());
		if (m_exitButton.MouseIsOnButton())
			m_exitButton.GetText().setFillColor(m_exitButton.GetHoverColor());
		else
			m_exitButton.GetText().setFillColor(m_exitButton.GetIdleColor());
		if (m_playButton.MouseIsOnButton())
			m_playButton.GetText().setFillColor(m_playButton.GetHoverColor());
		else
			m_playButton.GetText().setFillColor(m_playButton.GetIdleColor());
		break;
	}
		case sf::Event::MouseButtonReleased:
	{
			if (m_rulesButton.MouseIsOnButton())
			{
				m_rulesButton.GetText().setFillColor(m_rulesButton.GetHoverColor());
				m_states->push(new RulesState(*m_window, m_states));
			}
			if (m_exitButton.MouseIsOnButton())
			{
				m_exitButton.GetText().setFillColor(m_exitButton.GetHoverColor());
				m_states->pop();
				m_window->close();
			}
			if (m_playButton.MouseIsOnButton())
			{
				m_playButton.GetText().setFillColor(m_playButton.GetHoverColor());
				m_states->push(new GameState(*m_window, m_states));
			}
			break;
	}
		case sf::Event::MouseButtonPressed:
		{
			if (m_rulesButton.MouseIsOnButton())
				m_rulesButton.GetText().setFillColor(m_rulesButton.GetActiveColor());
			else
				m_rulesButton.GetText().setFillColor(m_rulesButton.GetIdleColor());
			if (m_exitButton.MouseIsOnButton())
				m_exitButton.GetText().setFillColor(m_exitButton.GetActiveColor());
			else
				m_exitButton.GetText().setFillColor(m_exitButton.GetIdleColor());
			if (m_playButton.MouseIsOnButton())
				m_playButton.GetText().setFillColor(m_playButton.GetActiveColor());
			else
				m_playButton.GetText().setFillColor(m_playButton.GetIdleColor());
			break;
		}
		default:
			break;

	}
}
