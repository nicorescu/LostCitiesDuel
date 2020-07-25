#include "pch.h"
#include "CppUnitTest.h"
#include "..\LostCityDuelsImplement\Card.h"

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
}
