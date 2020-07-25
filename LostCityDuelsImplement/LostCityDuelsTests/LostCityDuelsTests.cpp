#include "pch.h"
#include "CppUnitTest.h"
#include "..\LostCityDuelsImplement\Expedition.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LostCityDuelsTests
{
	TEST_CLASS(CardTests)
	{
	public:
		
		TEST_METHOD(Constructor)
		{
			Card card(Card::Colour::blue, Card::CardValues::fifthCard);
			Assert::IsTrue(card.GetColor() == Card::Colour::blue);
			Assert::IsTrue(card.GetValue() == Card::CardValues::fifthCard);
		}
		TEST_METHOD(Print)
		{
			Card card(Card::Colour::blue, Card::CardValues::fifthCard);
			std::stringstream stream;
			stream << card;
			Assert::AreEqual(std::string("Bl  5 "), stream.str(), L"If you see this i failed =(");
		}
		TEST_METHOD(MoveConstructor)
		{
			Card card(Card::Colour::blue, Card::CardValues::fifthCard);
			Card other(std::move(card));
			Assert::IsTrue(other.GetColor() == Card::Colour::blue);
			Assert::IsTrue(other.GetValue() == Card::CardValues::fifthCard);
			Assert::IsTrue(card.GetColor() == Card::Colour::none);
			Assert::IsTrue(card.GetValue() == Card::CardValues::none);
		}
		TEST_METHOD(AssigmentOperatorOverload)
		{
			Card card(Card::Colour::blue, Card::CardValues::fifthCard);
			Card other = card;
			Assert::IsTrue(other.GetColor() == Card::Colour::blue);
			Assert::IsTrue(other.GetValue() == Card::CardValues::fifthCard);
		}
		TEST_METHOD(CopyConstructor)
		{
			Card card(Card::Colour::blue, Card::CardValues::fifthCard);
			Card other(card);
			Assert::IsTrue(other.GetColor() == Card::Colour::blue);
			Assert::IsTrue(other.GetValue() == Card::CardValues::fifthCard);
		}

	};
	TEST_CLASS(ExpeditionTests)
	{
	public:
		
		TEST_METHOD(Constructor)
		{
			Expedition examplee(Card::Colour::blue);
			Assert::IsTrue(examplee.GetColor() == Card::Colour::blue);
			Assert::IsTrue(examplee.GetScore() == 0);
		}
		TEST_METHOD(CardOrder)
		{
			Expedition example(Card::Colour::red);
			Card card(Card::Colour::red, Card::CardValues::fifthCard);
			example.GetPlayedCards().emplace_back(card);
			Card badCard(Card::Colour::red, Card::CardValues::thirdCard);
			Assert::IsFalse(example.CardsAreInAscendingOrder(badCard));
			Card goodCard(Card::Colour::red, Card::CardValues::seventhCard);
			Assert::IsTrue(example.CardsAreInAscendingOrder(goodCard));
		}
		TEST_METHOD(Reset)
		{
			Expedition example(Card::Colour::gold);
			example.GetPlayedCards().emplace_back(Card(Card::Colour::gold, Card::CardValues::fourthCard));
			example.ResetExpedition();
			Assert::IsTrue(example.GetPlayedCards().size() == 0);
		}
		TEST_METHOD(AssignmentOperator)
		{
			Expedition expedition(Card::Colour::gold);
			Expedition anotherExpedition(Card::Colour::red);
			expedition = anotherExpedition;
			Assert::IsTrue(expedition.GetColor() == anotherExpedition.GetColor());
			Assert::IsTrue(expedition.GetScore() == anotherExpedition.GetScore());
		}
		TEST_METHOD(CopyConstructor)
		{
			Expedition expedition(Card::Colour::gold);
			Expedition anotherExpedition(expedition);
			Assert::IsTrue(expedition.GetColor() == anotherExpedition.GetColor());
			Assert::IsTrue(expedition.GetScore() == anotherExpedition.GetScore());
		}
		TEST_METHOD(MultiplierCalculation)
		{
			Expedition expedition(Card::Colour::gold);
			expedition.GetPlayedCards().emplace_back(Card(Card::Colour::gold, Card::CardValues::investition));
			expedition.GetPlayedCards().emplace_back(Card(Card::Colour::gold, Card::CardValues::investition));
			expedition.GetPlayedCards().emplace_back(Card(Card::Colour::gold, Card::CardValues::secondCard));
			Assert::IsTrue(expedition.InvestmentCount() == 3);
		}
	};
}
