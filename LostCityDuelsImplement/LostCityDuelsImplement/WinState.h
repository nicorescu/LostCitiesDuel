#pragma once
#include "State.h"
class WinState :
	public State
{
public:
	WinState(sf::RenderWindow& window, std::stack <State*>* states);
	void InitializeButtons(sf::Font& font);
	void Draw();
	void Render(sf::RenderTarget& target) override;
	void UpdateEvents(sf::Event& event) override;
private:
	Button m_mainMenuButton;
	sf::Font m_font;
	sf::Texture texture;
	sf::RectangleShape m_background;
};

