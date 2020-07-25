#include "NameSelectionState.h"

NameSelectionState::NameSelectionState(sf::RenderWindow& window, std::stack<State*>* states) : State(window, states)
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

void NameSelectionState::InitializeButtons(sf::Font& font)
{
	std::string play = "READY";

	sf::Color idleColor(sf::Color::White);
	sf::Color hoverColor(sf::Color::Yellow);
	sf::Color activeColor(sf::Color::Red);

	m_playButton.SetButtonAttributes((uint16_t)(m_window->getSize().x / 2 - m_playButton.GetText().getGlobalBounds().width / 2), (uint16_t)(m_window->getSize().y / 2), font, play, idleColor, hoverColor, activeColor);
	m_playerNameBox.setSize(sf::Vector2f(900, 100));
	m_playerNameBox.setPosition(m_window->getSize().x / 2 - m_playerNameBox.getSize().x/2 +200, m_window->getSize().y / 2  - 400);
	m_playerNameBox.setOutlineColor(sf::Color::White);
	m_playerNameBox.setFillColor(sf::Color::Transparent);
	m_playerNameBox.setOutlineThickness(10.0f);
}

void NameSelectionState::Draw()
{
	m_window->draw(m_background);
	m_playButton.Render(*m_window);
	sf::Text text;
	text.setFillColor(sf::Color::White);
	text.setString(m_playerName);
	text.setCharacterSize(100);
	text.setFont(m_font);
	text.setPosition(m_window->getSize().x / 2 - text.getGlobalBounds().width / 2, m_window->getSize().y / 2 - text.getGlobalBounds().height / 2-380);
	m_window->draw(text);
	m_window->draw(m_playerNameBox);
	sf::Text inputNameLabel;
	inputNameLabel.setString("Enter your name: ");
	inputNameLabel.setCharacterSize(100);
	inputNameLabel.setFont(m_font);
	inputNameLabel.setPosition(50, m_playerNameBox.getPosition().y);
	m_window->draw(inputNameLabel);
}

void NameSelectionState::Render(sf::RenderTarget& target)
{
	Draw();
}

void NameSelectionState::updateState()
{
}

void NameSelectionState::UpdateEvents(sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::MouseMoved:
	{
		if (m_playButton.MouseIsOnButton())
			m_playButton.GetText().setFillColor(m_playButton.GetHoverColor());
		else
			m_playButton.GetText().setFillColor(m_playButton.GetIdleColor());
		break;
	}
	case sf::Event::MouseButtonReleased:
	{
		if (m_playButton.MouseIsOnButton())
		{
			m_playButton.GetText().setFillColor(m_playButton.GetHoverColor());
			//GameState myGameState(*m_window, m_states);
			//myGameState.GetPlayer().SetName(m_playerName);
			m_states->push(new GameState(*m_window, m_states));
		}
		break;
	}
	case sf::Event::MouseButtonPressed:
	{
		if (m_playButton.MouseIsOnButton())
			m_playButton.GetText().setFillColor(m_playButton.GetActiveColor());
		else
			m_playButton.GetText().setFillColor(m_playButton.GetIdleColor());
		break;
	}
	case sf::Event::TextEntered:
	{
		char addedLetter;
		addedLetter = (char)event.text.unicode;
		if (event.text.unicode!='\b' && m_playerName.size() < 10)
		{
			m_playerName += addedLetter;
			Draw();
		}
		else if (event.text.unicode == '\b')
		{
			if (m_playerName.size() != 0)
			{
				m_playerName.erase(m_playerName.size() - 1, 1);
				Draw();
			}
		}
	}
	default:
		break;
	}
}

std::string NameSelectionState::GetPlayerName()
{
	return m_playerName;
}
