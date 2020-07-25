#include<SFML/Graphics.hpp>
class Button
{
public:
	Button(uint16_t x, uint16_t y, sf::Font& font, std::string text,sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	Button();
	void Render(sf::RenderTarget &target);  
	void SetButtonAttributes(uint16_t x, uint16_t y, sf::Font& font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	sf::Text& GetText();
	bool MouseIsOnButton();
	sf::Color GetIdleColor();
	sf::Color GetHoverColor();
	sf::Color GetActiveColor();
private:
	sf::Font m_font;
	sf::Text m_buttonText;
	sf::Color m_idleColor;
	sf::Color m_hoverColor;
	sf::Color m_activeColor;
};

