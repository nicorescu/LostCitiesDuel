#pragma once
#include<string>
#include<array>
#include<algorithm>
#include<vector>
#include<iostream>
#include<stack>
#include"Expedition.h"


class Player
{
public:
	Player()=default;
	Player(const std::string&);
	~Player();

	friend std::ostream& operator<<(std::ostream& out, const Player& player);
public:
	std::vector<Card>& GetPlayerHand();
	std::string GetPlayerName();
	int16_t& GetCurrentScore();
	std::array <Expedition, 5> GetExpeditions();

	void SetTotalScore();
	void SetName(const std::string& chosenName);
	void SetScore(int newScore);
public:
	void PrintCurrentHand();
	void PrintExpeditionScores();
	void PrintCurrentScore();

	void SortHand();
	void PlaceCardInPlayerHand(Card card, int index);
	void AddCardToExpedition(int index);
	void AddCardToDiscardPile(int index, std::stack<Card>& pile);
	void RemoveCardFromHand(int index);
	void ResetPlayer();

private:
	std::string m_name;
	std::vector<Card> m_playerHand;
	std::array <Expedition, 5> m_expeditions;
	int16_t m_currentScore;
};

