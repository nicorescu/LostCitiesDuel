#pragma once
#include "State.h"
#include"RulesState.h"
class PauseState :
	public State
{
public:
	PauseState(sf::RenderWindow& window, std::stack <State*>* states);

	void InitializeButtons(sf::Font& font);
	void Draw();
	void Render(sf::RenderTarget& target) override;
	void UpdateEvents(sf::Event& event) override;
private:
	Button m_resumeButton;
	Button m_rulesButton;
	Button m_mainMenuButton;
	sf::Font m_font;
	sf::Texture texture;
	sf::RectangleShape m_background;
	const uint16_t number_of_buttons = 3;
};

