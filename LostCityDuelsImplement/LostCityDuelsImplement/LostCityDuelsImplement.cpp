#include <iostream>
#include "Game.h"
#include<fstream>
#include<time.h>
#include "LostCityDuelGame.h"

int main()
{
	LostCityDuelGame game;
	
	int choice;
	std::cout << "1---> Play the GUI game.\n2---> Play the game in multiplayer mode via console, bring a friend =).\n";
	std::cout << "Your pick: ";
	std::cin >> choice;
	switch (choice)
	{
	case 1:
	{
		Game game;
		game.RunGame();
		game.Render();
		break;
	}
	case 2:
	{
		game.RunGame();
		break;
	}
	}
}