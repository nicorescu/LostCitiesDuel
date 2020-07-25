//#pragma once
//#include <iostream>
//#include <SFML/Graphics.hpp>
//
//class GameGraphics {
//public:
//	static void WindowDisplay(sf::RenderWindow &window)
//	{
//		
//		sf::RectangleShape exp1(sf::Vector2f(window.getSize().x / 5, window.getSize().y - window.getSize().y / 8));
//		sf::RectangleShape exp2(sf::Vector2f(window.getSize().x / 5, window.getSize().y - window.getSize().y / 8));
//		sf::RectangleShape exp3(sf::Vector2f(window.getSize().x / 5, window.getSize().y - window.getSize().y / 8));
//		sf::RectangleShape exp4(sf::Vector2f(window.getSize().x / 5, window.getSize().y - window.getSize().y / 8));
//		sf::RectangleShape exp5(sf::Vector2f(window.getSize().x / 5, window.getSize().y - window.getSize().y / 8));
//
//		sf::RectangleShape topBar(sf::Vector2f(window.getSize().x, window.getSize().y / 13));
//		sf::RectangleShape bottomBar(sf::Vector2f(window.getSize().x, window.getSize().y));
//
//		sf::RectangleShape drawingDeck(sf::Vector2f((window.getSize().y / 15), window.getSize().y / 15));
//
//		sf::RectangleShape GoldenPile(sf::Vector2f((window.getSize().y / 14), window.getSize().y / 14));
//		sf::RectangleShape BluePile(sf::Vector2f((window.getSize().y / 14), window.getSize().y / 14));
//		sf::RectangleShape WhitePile(sf::Vector2f((window.getSize().y / 14), window.getSize().y / 14));
//		sf::RectangleShape GreenPile(sf::Vector2f((window.getSize().y / 14), window.getSize().y / 14));
//		sf::RectangleShape RedPile(sf::Vector2f((window.getSize().y / 14), window.getSize().y / 14));
//
//		sf::Texture GoldenPileTexture;
//		sf::Texture BluePileTexture;
//		sf::Texture WhitePileTexture;
//		sf::Texture GreenPileTexture;
//		sf::Texture RedPileTexture;
//
//		GoldenPileTexture.loadFromFile("GoldenPile.jpg");
//		BluePileTexture.loadFromFile("BluePile.jpg");
//		WhitePileTexture.loadFromFile("WhitePile.jpg");
//		GreenPileTexture.loadFromFile("GreenPile.jpg");
//		RedPileTexture.loadFromFile("RedPile.jpg");
//
//		GoldenPile.setTexture(&GoldenPileTexture);
//		BluePile.setTexture(&BluePileTexture);
//		WhitePile.setTexture(&WhitePileTexture);
//		GreenPile.setTexture(&GreenPileTexture);
//		RedPile.setTexture(&RedPileTexture);
//
//
//
//
//		sf::Texture yellow;
//		yellow.loadFromFile("gold.jpg");
//		sf::Texture blue;
//		blue.loadFromFile("blue.jpg");
//		sf::Texture white;
//		white.loadFromFile("white.jpg");
//		sf::Texture green;
//		green.loadFromFile("green.jpg");
//		sf::Texture red;
//		red.loadFromFile("red.jpg");
//		sf::Texture DeckTexture;
//		DeckTexture.loadFromFile("DrawingDeck.jpg");
//
//		exp1.setTexture(&yellow);
//		exp2.setTexture(&blue);
//		exp3.setTexture(&white);
//		exp4.setTexture(&green);
//		exp5.setTexture(&red);
//		drawingDeck.setTexture(&DeckTexture);
//
//		topBar.setFillColor(sf::Color(190, 190, 0, 255));
//		bottomBar.setFillColor(sf::Color(190, 190, 0, 255));
//
//
//
//		exp1.setPosition(0, 0.f);
//		int count = 1;
//		exp2.setPosition((window.getSize().x / 5) * count, 0.f);
//		count++;
//		exp3.setPosition((window.getSize().x / 5) * count, 0.f);
//		count++;
//		exp4.setPosition((window.getSize().x / 5) * count, 0.f);
//		count++;
//		exp5.setPosition((window.getSize().x / 5) * count, 0.f);
//		count++;
//
//		drawingDeck.setPosition((exp5.getPosition().x/5)*5.9,topBar.getSize().y/10);
//		GoldenPile.setPosition(exp1.getSize().x / 3, exp1.getSize().y / 2);
//		BluePile.setPosition(exp2.getSize().x * 1.5, exp2.getSize().y / 2);
//		WhitePile.setPosition(exp3.getSize().x * 2.5, exp3.getSize().y / 2);
//		GreenPile.setPosition(exp4.getSize().x * 3.5, exp4.getSize().y / 2);
//		RedPile.setPosition(exp5.getSize().x * 4.5, exp5.getSize().y / 2);
//
//		/*exp1.setFillColor(sf::Color::Yellow);
//		exp2.setFillColor(sf::Color(0,0,255,255));
//		exp3.setFillColor(sf::Color::White);
//		exp5.setFillColor(sf::Color::Red);*/
//		//sf::Color array1 [3]= { sf::Color::Cyan,sf::Color::Magenta,sf::Color::Green };
//		while (window.isOpen())
//		{
//			sf::Event evnt;
//			while (window.pollEvent(evnt))
//			{
//
//				switch (evnt.type)
//				{
//				case sf::Event::Closed:
//					window.close();
//					break;
//				case sf::Event::Resized:
//					std::cout << "Window size: " << evnt.size.width << " " << evnt.size.height << std::endl;
//					printf("New window width %i and window height %i \n", evnt.size.width, evnt.size.height);
//					break;
//				case sf::Event::TextEntered:
//					if (evnt.text.unicode < 128)
//						printf("%c", evnt.text.unicode);
//					break;
//				}
//
//			}
//			window.clear();
//			window.draw(exp1);
//			window.draw(exp2);
//			window.draw(exp3);
//			window.draw(exp4);
//			window.draw(exp5);
//			window.draw(topBar);
//			window.draw(drawingDeck);
//			window.draw(GoldenPile);
//			window.draw(BluePile);
//			window.draw(WhitePile);
//			window.draw(GreenPile);
//			window.draw(RedPile);
//			window.display();	
//		}
//	}
//};