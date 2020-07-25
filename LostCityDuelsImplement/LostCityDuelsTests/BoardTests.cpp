#include "pch.h"
#include "CppUnitTest.h"
#include "..\LostCityDuelsImplement\Board.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LostCityDuelsTests
{
	TEST_CLASS(BoardTests)
	{
		TEST_METHOD(DrawFromDrawingDeck)
		{
			Board board;
			Card exampleCard(Card::Colour::gold, Card::CardValues::eighthCard);
			board.EmplaceCard(exampleCard);
			Card anotherCard(board.ExtractCardFromDeck());
			Assert::IsTrue(anotherCard == exampleCard);
			Assert::IsTrue(board.GetDrawingDeck().size() == 0);
		}
		TEST_METHOD(CheckIfAnyDiscardPileNotEmpty)
		{
			Board board;
			Card exampleCard(Card::Colour::gold, Card::CardValues::eighthCard);
			board.GetPile(2).push(exampleCard);
			Assert::IsTrue(board.CheckForAllDiscardPiles());
		}
		TEST_METHOD(CheckIfDiscardPileCanNotBeDrawnFrom)
		{
			Board board;
			Assert::IsTrue(board.CheckSingleDiscardPile(2) == Card(Card::Colour::red, Card::CardValues::invalidCard));
		}
		TEST_METHOD(BoardReset)
		{
			Board board;
			Card exampleCard(Card::Colour::gold, Card::CardValues::eighthCard);
			board.GetPile(2).push(exampleCard);
			board.GetPile(1).push(exampleCard);
			board.GetPile(0).push(exampleCard);
			board.ResetBoard();
			Assert::IsFalse(board.CheckForAllDiscardPiles());
		}
	};
	
}
