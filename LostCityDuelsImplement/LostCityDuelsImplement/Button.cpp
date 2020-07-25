#include "Button.h"



Button::Button(uint16_t x, uint16_t y, sf::Font& font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	
	
	

	

}

Button::Button()
{
	//empty
}

void Button::Render(sf::RenderTarget &target)
{
	target.draw(m_buttonText);
}

void Button::SetButtonAttributes(uint16_t x, uint16_t y, sf::Font& font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	m_idleColor = idleColor;
	m_hoverColor = hoverColor;
	m_activeColor = activeColor;

	m_font = font;
	m_buttonText.setFont(m_font);
	m_buttonText.setString(text);
	m_buttonText.setFillColor(m_idleColor);
	m_buttonText.setPosition(x, y);
	m_buttonText.setCharacterSize(50);
	m_buttonText.setOutlineThickness(2.f);

}

sf::Text& Button::GetText()
{
	return m_buttonText;
}

bool Button::MouseIsOnButton()
{
	sf::Mouse mouse;
	if (mouse.getPosition().x >= m_buttonText.getPosition().x && mouse.getPosition().x <= (m_buttonText.getPosition().x + m_buttonText.getLocalBounds().width)
		&& mouse.getPosition().y >= m_buttonText.getPosition().y && mouse.getPosition().y <= (m_buttonText.getPosition().y + m_buttonText.getLocalBounds().height))
			return true;
	return false;

}

sf::Color Button::GetIdleColor()
{
	return m_idleColor;
}

sf::Color Button::GetHoverColor()
{
	return m_hoverColor;
}

sf::Color Button::GetActiveColor()
{
	return m_activeColor;
}
