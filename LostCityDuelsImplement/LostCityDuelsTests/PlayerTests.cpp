#include "pch.h"
#include "CppUnitTest.h"
#include "..\LostCityDuelsImplement\Player.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LostCityDuelsTests
{
	TEST_CLASS(PlayerTest)
	{
		TEST_METHOD(Constructor)
		{
			Player player("Fornetti");
			Assert::AreEqual(std::string("Fornetti"), player.GetPlayerName());
			for (int index = 0; index < player.GetExpeditions().size(); index++)
				Assert::IsTrue(player.GetExpeditions()[index].GetColor() == Card::Colour(index));
			Assert::IsTrue(player.GetCurrentScore() == 0);
		}
		TEST_METHOD(ExpeditionInsertion)
		{
			Player player("Fornetti");
			player.GetPlayerHand().emplace_back(Card(Card::Colour::blue, Card::CardValues::fifthCard));
			player.AddCardToExpedition(0);
			Assert::IsTrue(player.GetPlayerHand().size() == 0);
			Assert::IsTrue(player.GetExpeditions()[1].GetPlayedCards()[0].GetColor() == Card::Colour::blue);
			Assert::IsTrue(player.GetExpeditions()[1].GetPlayedCards()[0].GetValue() == Card::CardValues::fifthCard);
		}
		TEST_METHOD(AddAtBadExpeditionIndex)
		{
			Player player("Fornetti");
			player.GetPlayerHand().emplace_back(Card(Card::Colour::blue, Card::CardValues::fifthCard));
			Assert::ExpectException<std::out_of_range>([&player]()
				{
					player.AddCardToExpedition(int(Card::Colour::none));
				});
		}
		TEST_METHOD(DiscardPileInsertion)
		{
			Player player("Fornetti");
			player.GetPlayerHand().emplace_back(Card(Card::Colour::blue, Card::CardValues::fifthCard));
			std::stack<Card> aDiscardPile;
			player.AddCardToDiscardPile(0, aDiscardPile);
			Assert::IsTrue(aDiscardPile.top() == Card(Card::Colour::blue, Card::CardValues::fifthCard));
			Assert::IsTrue(player.GetPlayerHand().size() == 0);
		}
		TEST_METHOD(AddAtBadDiscardPileIndex)
		{
			Player player("Fornetti");
			std::stack<Card> aDiscardPile;
			player.GetPlayerHand().emplace_back(Card(Card::Colour::blue, Card::CardValues::fifthCard));
			Assert::ExpectException<std::out_of_range>([&player, &aDiscardPile]()
				{
					player.AddCardToDiscardPile(int(Card::Colour::none), aDiscardPile);
				});
		}
	};
}
