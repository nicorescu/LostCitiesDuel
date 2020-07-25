#include "LostCityDuelGame.h"
#include "Board.h"
#include <exception>
#include <iomanip>
#include "..\Logging\Logger.h"
#include "PlayerRender.h"
#include "SFML/Network.hpp"

void LostCityDuelGame::RunGame()
{
	sf::TcpSocket socket;
	sf::IpAddress ipAddress = sf::IpAddress::getLocalAddress();
	char connectionType;
	std::cout << "Choose your connection type: ";
	std::cin >> connectionType;
	if (connectionType == 's')
	{
		sf::TcpListener listener;
		listener.listen(3014);
		listener.accept(socket);
		std::cout << "You are connected as server \n";
	}
	else if (connectionType == 'c')
	{
		socket.connect(ipAddress, 3014);
		std::cout << "You are connected as client \n";
	}

	std::ofstream logFile("log.log", std::ios::app);
	Logger logger(logFile, Logger::Level::Info);
	logger.Log("Game running..", Logger::Level::Info);


	std::string name, receivedName;
	std::cout << "Enter player1 name: ";
	std::cin >> name;
	Player firstPlayer(name);
	Player secondPlayer;
	sf::Packet packet;
	packet << name;
	socket.send(packet);
	socket.receive(packet);

	if (packet >> receivedName)
	{
		secondPlayer.SetName(receivedName);
	}
	std::reference_wrapper<Player>currentPlayingPlayer = firstPlayer;
	std::reference_wrapper<Player>nextPlayingPlayer = secondPlayer;

	uint16_t totalScorePlayer1 = 0;
	uint16_t totalScorePlayer2 = 0;
	uint16_t currentRound = 1;
	uint16_t player1Wins = 0;
	uint16_t player2Wins = 0;

	while (currentRound <= 3)
	{

		std::cout << "Round " << currentRound << "\n\n";
		logger.Log("Round " + std::to_string(currentRound) + " has started ", Logger::Level::Info);
		Board board;
		board.GenerateDrawingDeck();
		board.GeneratePlayerHand(firstPlayer);
		board.GeneratePlayerHand(secondPlayer);

		while (board.GetDrawingDeck().size() != 0)
		{

			bool decision;
			uint16_t expeditionIndex, chosenCardIndex;
			std::cout << "\t\t\t---" << currentPlayingPlayer.get().GetPlayerName() << "'s turn---";
			currentPlayingPlayer.get().PrintCurrentHand();
			currentPlayingPlayer.get().PrintExpeditionScores();

			board.PrintDiscardPiles();
			std::cout << "\nChoose if you wanna add a card to an expedition(0) or discard one(1): ";
			std::cin >> decision;
			while (!std::cin.good())
			{
				std::cout << "\nInvalid input! please insert a value that is 0 or 1.";
				std::cin.clear();
				std::cin.ignore(UINT8_MAX, '\n');
				std::cin >> decision;
			}
			switch (decision)
			{
			case 0:
				logger.Log("Player " + currentPlayingPlayer.get().GetPlayerName() + " is currently playing a card.", Logger::Level::Info);
				while (true)
				{
					currentPlayingPlayer.get().PrintCurrentHand();
					std::cout << "\nChoose the card that you want to play: ";
					std::cin >> chosenCardIndex;
					while (!std::cin.good())
					{
						std::cout << "\nInvalid input! ";
						std::cin.clear();
						std::cin.ignore(UINT16_MAX, '\n');
						std::cin >> chosenCardIndex;
					}
					try
					{
						Card card(currentPlayingPlayer.get().GetPlayerHand().at(chosenCardIndex - 1));
						sf::Packet packet;
						std::string sentCardColour = currentPlayingPlayer.get().GetPlayerHand()[chosenCardIndex - 1].GetCardColourString();
						std::string sentCardValue = currentPlayingPlayer.get().GetPlayerHand()[chosenCardIndex - 1].GetCardValueString();
						std::string receivedCardColours, receivedCardValue;

						currentPlayingPlayer.get().AddCardToExpedition(chosenCardIndex - 1);
						currentPlayingPlayer.get().SetTotalScore();
						std::cout << "\n" << currentPlayingPlayer.get().GetPlayerName() << "'s total score is:" << currentPlayingPlayer.get().GetCurrentScore() << std::endl;
						int sentScore = currentPlayingPlayer.get().GetCurrentScore();
						int receivedScore;

						packet << sentCardColour << sentCardValue << sentScore;
						socket.send(packet);
						socket.receive(packet);
						if (packet >> receivedCardColours >> receivedCardValue >> receivedScore)
						{
							std::cout << "Player " << nextPlayingPlayer.get().GetPlayerName() << " played card with colour " << receivedCardColours << " and value " << receivedCardValue << "\n";
							std::cout << nextPlayingPlayer.get().GetPlayerName() << receivedScore;
						}
						logger.Log("Card placed.", Logger::Level::Info);
						break;
					}
					catch (const char* message)
					{
						std::cout << "\n" << message;
					}
					catch (const std::out_of_range)
					{
						std::cout << "Your hand contains cards from 1 to 8. \n";
					}

				}
				break;
			case 1:
				logger.Log("Player " + currentPlayingPlayer.get().GetPlayerName() + " is discarding a card.", Logger::Level::Info);
				while (true)
				{
					currentPlayingPlayer.get().PrintCurrentHand();
					board.PrintDiscardPiles();
					std::cout << "\nChoose the card that you want to discard ";
					std::cin >> chosenCardIndex;
					try
					{
						std::string sentCardColour = currentPlayingPlayer.get().GetPlayerHand()[chosenCardIndex - 1].GetCardColourString();
						std::string sentCardValue = currentPlayingPlayer.get().GetPlayerHand()[chosenCardIndex - 1].GetCardValueString();
						std::string receivedCardColours, receivedCardValue;
						sf::Packet packet;
						packet << sentCardColour << sentCardValue;
						socket.send(packet);
						socket.receive(packet);
						if (packet >> receivedCardColours >> receivedCardValue)
						{
							std::cout << "Player " << nextPlayingPlayer.get().GetPlayerName() << " discard card with colour " << receivedCardColours << " and value " << receivedCardValue << "\n";
						}

						currentPlayingPlayer.get().AddCardToDiscardPile(chosenCardIndex - 1, board.GetPile((int)currentPlayingPlayer.get().GetPlayerHand().at(chosenCardIndex - 1).GetColor()));
						logger.Log("Card discarded", Logger::Level::Info);
						break;
					}
					catch (const std::out_of_range & exception)
					{
						std::cout << exception.what() << '\n';
					}

				}
				break;
			}
			currentPlayingPlayer.get().PrintExpeditionScores();
			board.PrintDiscardPiles();
			std::cout << "\nChoose if you wanna draw a card from the drawing deck(0) or the discard pile(1):";
			std::cin >> decision;
			while (!std::cin.good())
			{
				std::cout << "\nInvalid input! please insert a value that is 0 or 1.";
				std::cin.clear();
				std::cin.ignore(UINT8_MAX, '\n');
				std::cin >> decision;
			}

			switch (decision)
			{

			case 0:
			{
				logger.Log("Player " + currentPlayingPlayer.get().GetPlayerName() + " has drawn a card", Logger::Level::Info);
				currentPlayingPlayer.get().PlaceCardInPlayerHand(board.ExtractCardFromDeck(), chosenCardIndex - 1);
				std::string receivedPlayerAction;
				sf::Packet packet;
				packet << "Player " + currentPlayingPlayer.get().GetPlayerName() + " decided to draw from deck\n";
				socket.send(packet);
				socket.receive(packet);
				if (packet >> receivedPlayerAction)
					std::cout << receivedPlayerAction;
				break;
			}
			case 1:
				logger.Log("Player " + currentPlayingPlayer.get().GetPlayerName() + " has drawn a card", Logger::Level::Info);
				while (true)
				{
					if (!board.CheckForAllDiscardPiles())
					{
						currentPlayingPlayer.get().PlaceCardInPlayerHand(board.ExtractCardFromDeck(), chosenCardIndex - 1);
						std::cout << "\n All discard piles were empty so you drew a card.";
						break;
					}
					else
					{

						std::cout << "\nChoose which discard pile you want to draw from: ";
						std::cin >> expeditionIndex;
						Card invalidCard(Card::Colour::red, Card::CardValues::invalidCard);
						while (board.CheckSingleDiscardPile(expeditionIndex - 1) == invalidCard)
						{
							std::cout << "\nThis discard pile is empty. Please pick another discard pile that has cards: ";
							std::cin.clear();
							std::cin >> expeditionIndex;
						}
						while (!std::cin.good())
						{
							std::cout << "\nThat discard pile doesn't exist. Please select a valid Discard Pile(between 0 and 4): ";
							std::cin.clear();
							std::cin.ignore(UINT16_MAX, '\n');
							std::cin >> expeditionIndex;
						}
						try
						{
							sf::Packet packet;
							std::string sentCardColour = board.GetPile(expeditionIndex - 1).top().GetCardColourString();
							std::string sentCardValue = board.GetPile(expeditionIndex - 1).top().GetCardValueString();
							std::string receivedCardColour, receivedCardValue;
							packet << sentCardColour << sentCardValue;
							socket.send(packet);
							socket.receive(packet);
							if (packet >> sentCardColour >> sentCardValue)
							{
								std::cout << "Player " << nextPlayingPlayer.get().GetPlayerName() << " drew card with colour " << sentCardColour << " and value " << sentCardValue << "\n";
							}
							Card extractedCard(std::move(board.GetPile(expeditionIndex - 1).top()));
							board.GetPile(expeditionIndex - 1).pop();
							currentPlayingPlayer.get().PlaceCardInPlayerHand(extractedCard, chosenCardIndex - 1);
							break;
						}
						catch (const std::out_of_range)
						{
							std::cout << "Non-existent discard pile number!Pick a number between 0 and 4! \n";
						}
						catch (const char* message)
						{
							std::cout << message;
						}
					}
				}
				break;
			}
			std::cout << "\n" << currentPlayingPlayer.get().GetPlayerName() << "'s player hand is: ";
			currentPlayingPlayer.get().PrintCurrentHand();
			std::cout << "\nCycle completed\n";
			std::cout << "\nThere are: " << board.GetDrawingDeck().size() << " cards left in the deck.\n";
			std::swap(currentPlayingPlayer, nextPlayingPlayer);

		}
		logger.Log("Round" + std::to_string(currentRound) + " has ended", Logger::Level::Info);
		currentRound++;
		firstPlayer.ResetPlayer();
		secondPlayer.ResetPlayer();
		board.ResetBoard();
		if (firstPlayer.GetCurrentScore() > secondPlayer.GetCurrentScore())
			player1Wins++;
		else
			player2Wins++;
	}
	std::cout << '\n' << firstPlayer.GetPlayerName() << "'s score is: " << firstPlayer.GetCurrentScore() << '\n';
	std::cout << '\n' << secondPlayer.GetPlayerName() << "'s score is: " << secondPlayer.GetCurrentScore() << '\n';
	if (player1Wins > player2Wins)
	{
		std::cout << '\n' << firstPlayer.GetPlayerName() << " wins!";
	}
	else
		std::cout << '\n' << secondPlayer.GetPlayerName() << " wins!";

}
