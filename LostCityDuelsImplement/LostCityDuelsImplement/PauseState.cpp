#include "PauseState.h"

PauseState::PauseState(sf::RenderWindow& window, std::stack <State*>* states) : State(window, states)
{
	if (!m_font.loadFromFile("Cardinal.ttf"))
	{
		return;
	}
	texture.loadFromFile("Pause.jpg");
	m_background.setSize(sf::Vector2f(m_window->getSize().x, m_window->getSize().y));
	m_background.setTexture(&texture);
	InitializeButtons(m_font);
}

void PauseState::InitializeButtons(sf::Font& font)
{
	std::string resume = "RESUME";
	std::string rules = "RULES";
	std::string mainMenu = "MAIN MENU";

	sf::Color idleColor(sf::Color::White);
	sf::Color hoverColor(sf::Color::Yellow);
	sf::Color activeColor(sf::Color::Red);

	m_resumeButton.SetButtonAttributes((uint16_t)(m_window->getSize().x / 2 - m_resumeButton.GetText().getGlobalBounds().width/2), (uint16_t)(m_window->getSize().y / (number_of_buttons + 1) * 1 + 400), font, resume, idleColor, hoverColor, activeColor);
	m_rulesButton.SetButtonAttributes((uint16_t)(m_window->getSize().x / 2 - m_rulesButton.GetText().getGlobalBounds().width / 2), (uint16_t)(m_window->getSize().y / (number_of_buttons + 1) * 1.5 + 400), font, rules, idleColor, hoverColor, activeColor);
	m_mainMenuButton.SetButtonAttributes((uint16_t)(m_window->getSize().x / 2 - m_mainMenuButton.GetText().getGlobalBounds().width / 2), (uint16_t)(m_window->getSize().y / (number_of_buttons + 1) * 2 + 400), font, mainMenu, idleColor, hoverColor, activeColor);
}

void PauseState::Draw()
{
	m_window->draw(m_background);
	m_resumeButton.Render(*m_window);
	m_rulesButton.Render(*m_window);
	m_mainMenuButton.Render(*m_window);
}

void PauseState::Render(sf::RenderTarget& target)
{
	Draw();
}

void PauseState::UpdateEvents(sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::MouseMoved:
	{
		if (m_resumeButton.MouseIsOnButton())
			m_resumeButton.GetText().setFillColor(m_resumeButton.GetHoverColor());
		else
			m_resumeButton.GetText().setFillColor(m_resumeButton.GetIdleColor());
		if (m_rulesButton.MouseIsOnButton())
			m_rulesButton.GetText().setFillColor(m_rulesButton.GetHoverColor());
		else
			m_rulesButton.GetText().setFillColor(m_rulesButton.GetIdleColor());
		if (m_mainMenuButton.MouseIsOnButton())
			m_mainMenuButton.GetText().setFillColor(m_mainMenuButton.GetHoverColor());
		else 
			m_mainMenuButton.GetText().setFillColor(m_mainMenuButton.GetIdleColor());
		break;
	}
	case sf::Event::MouseButtonReleased:
	{
		if (m_resumeButton.MouseIsOnButton())
		{
			m_resumeButton.GetText().setFillColor(m_resumeButton.GetHoverColor());
			m_states->pop();
		}
		else if (m_rulesButton.MouseIsOnButton())
		{
			m_rulesButton.GetText().setFillColor(m_rulesButton.GetHoverColor());
			m_states->push(new RulesState(*m_window, m_states));
		}
		else if (m_mainMenuButton.MouseIsOnButton())
		{
			m_mainMenuButton.GetText().setFillColor(m_mainMenuButton.GetHoverColor());
			m_states->pop();
			m_states->pop();
		}
		break;
	}
	case sf::Event::MouseButtonPressed:
	{
		if (m_resumeButton.MouseIsOnButton())
			m_resumeButton.GetText().setFillColor(m_resumeButton.GetActiveColor());
		else
			m_resumeButton.GetText().setFillColor(m_resumeButton.GetIdleColor());
		if (m_rulesButton.MouseIsOnButton())
			m_rulesButton.GetText().setFillColor(m_rulesButton.GetActiveColor());
		else
			m_rulesButton.GetText().setFillColor(m_rulesButton.GetIdleColor());
		if (m_mainMenuButton.MouseIsOnButton())
			m_mainMenuButton.GetText().setFillColor(m_mainMenuButton.GetActiveColor());
		else
			m_mainMenuButton.GetText().setFillColor(m_mainMenuButton.GetIdleColor());
	}
	default:
	{
		break;
	}
	}
		
			
}
