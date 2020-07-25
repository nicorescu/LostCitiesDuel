#include "RulesState.h"

RulesState::RulesState(sf::RenderWindow& window, std::stack <State*>* states):State(window, states)
{
	if (!m_font.loadFromFile("Cardinal.ttf"))
	{
		return;
	}

	for (int i = 0; i < 3; i++)
	{
		sf::Texture tex;
		tex.loadFromFile("Rules(" + std::to_string(i + 1) + ").jpg");
		m_background.push_back(tex);
	}
	backgroundShape.setTexture(&m_background[0]);
	backgroundShape.setSize(sf::Vector2f(m_window->getSize().x, m_window->getSize().y));
	InitializeButtons(m_font);
}

void RulesState::InitializeButtons(sf::Font& font)
{
	m_backButtonText.SetButtonAttributes(10, 10, font, "BACK", sf::Color::White, sf::Color::Yellow, sf::Color::Red);
	m_nextButton.SetButtonAttributes(m_window->getSize().x - m_backButtonText.GetText().getLocalBounds().width, m_window->getSize().y / 2 - m_nextButton.GetText().getLocalBounds().height / 2,
		font,"NEXT", sf::Color::White, sf::Color::Yellow, sf::Color::Red);
	m_previousButton.SetButtonAttributes(0, m_window->getSize().y / 2 - m_nextButton.GetText().getLocalBounds().height / 2, font, "PREVIOUS", sf::Color::White, sf::Color::Yellow, sf::Color::Red);
}

void RulesState::Draw()
{
	m_window->draw(backgroundShape);
	m_backButtonText.Render(*m_window);
	m_nextButton.Render(*m_window);
	m_previousButton.Render(*m_window);
}

bool RulesState::MouseIsOnPrevious()
{
	if (m_previousButton.MouseIsOnButton() == true)
		return true;
    return false;

}

bool RulesState::MouseIsOnNext()
{
	if (m_nextButton.MouseIsOnButton() == true)
		return true;
	return false;
}

void RulesState::MoveRulePagesForward()
{
	if (m_currentPage == 2)
		return;
	m_currentPage++;
	backgroundShape.setTexture(&m_background[m_currentPage]);
	backgroundShape.setSize(sf::Vector2f(m_window->getSize().x, m_window->getSize().y));

}

void RulesState::MoveRulePagesBackward()
{
	if (m_currentPage == 0)
		return;
	m_currentPage--;
	backgroundShape.setTexture(&m_background[m_currentPage]);
	backgroundShape.setSize(sf::Vector2f(m_window->getSize().x, m_window->getSize().y));
}

void RulesState::Render(sf::RenderTarget& target)
{
	Draw();
}

void RulesState::UpdateEvents(sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::MouseMoved:
	{
		if (m_backButtonText.MouseIsOnButton())
			m_backButtonText.GetText().setFillColor(m_backButtonText.GetHoverColor());
		else
			m_backButtonText.GetText().setFillColor(m_backButtonText.GetIdleColor());
		if (m_nextButton.MouseIsOnButton())
			m_nextButton.GetText().setFillColor(m_nextButton.GetHoverColor());
		else
			m_nextButton.GetText().setFillColor(m_nextButton.GetIdleColor());
		if (m_previousButton.MouseIsOnButton())
			m_previousButton.GetText().setFillColor(m_previousButton.GetHoverColor());
		else
			m_previousButton.GetText().setFillColor(m_previousButton.GetIdleColor());
		break;
	}
	case sf::Event::MouseButtonReleased:
	{
		if (m_backButtonText.MouseIsOnButton())
		{
			m_backButtonText.GetText().setFillColor(m_backButtonText.GetHoverColor());
			m_states->pop();
		}
		else if (m_nextButton.MouseIsOnButton())
		{
			m_nextButton.GetText().setFillColor(m_nextButton.GetHoverColor());
			MoveRulePagesForward();
		}
		else if (m_previousButton.MouseIsOnButton())
		{
			m_previousButton.GetText().setFillColor(m_previousButton.GetHoverColor());;
			MoveRulePagesBackward();
		}
		break;
	}
	case sf::Event::MouseButtonPressed:
	{
		if (m_backButtonText.MouseIsOnButton())
			m_backButtonText.GetText().setFillColor(m_backButtonText.GetActiveColor());
		else
			m_backButtonText.GetText().setFillColor(m_backButtonText.GetIdleColor());
		if (m_nextButton.MouseIsOnButton())
			m_nextButton.GetText().setFillColor(m_nextButton.GetActiveColor());
		else
			m_nextButton.GetText().setFillColor(m_nextButton.GetIdleColor());
		if (m_previousButton.MouseIsOnButton())
			m_previousButton.GetText().setFillColor(m_previousButton.GetActiveColor());
		else
			m_previousButton.GetText().setFillColor(m_previousButton.GetIdleColor());
		break;
	}
	default:
		break;
	}
	
}
