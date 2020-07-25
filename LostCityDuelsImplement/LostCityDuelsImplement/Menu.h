#pragma once
#include<SFML/Graphics.hpp>
#define NUMBER_OF_BUTTONS 2

class Menu
{
public:
	Menu(float width,float height);
	~Menu();
	void Draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem();

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text MenuText[NUMBER_OF_BUTTONS];
};

