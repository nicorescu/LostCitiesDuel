#include "Menu.h"

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("arial.ttf"))
	{
		// eroare
	}
	MenuText[0].setFont(font);
	MenuText[0].setFillColor(sf::Color::Red);
	MenuText[0].setCharacterSize(20);
	MenuText[0].setString("PLAY");
	MenuText[0].setPosition(sf::Vector2f(width / 2, height / (NUMBER_OF_BUTTONS+1) * 1));

	MenuText[1].setFont(font);
	MenuText[1].setFillColor(sf::Color::White);
	MenuText[1].setCharacterSize(20);
	MenuText[1].setString("EXIT");
	MenuText[1].setPosition(sf::Vector2f(width / 2, height / (NUMBER_OF_BUTTONS + 1) * 2));

	selectedItemIndex = 0;
}

Menu::~Menu()
{
}

void Menu::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < NUMBER_OF_BUTTONS; ++i)
	{
		window.draw(MenuText[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		MenuText[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		MenuText[selectedItemIndex].setFillColor(sf::Color::Red);
	}

}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < NUMBER_OF_BUTTONS)
	{
		MenuText[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		MenuText[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

int Menu::GetPressedItem()
{
	return selectedItemIndex;
}
