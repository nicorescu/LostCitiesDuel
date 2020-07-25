#include "Player.h"

Player::Player(const std::string& name) : m_name(name)
{
	for (int index = 0; index < m_expeditions.size(); index++)
		m_expeditions.at(index) = Expedition(Card::Colour(index));

	m_currentScore = 0;
}

Player::~Player()
{
	for (int i = 0; i < m_expeditions.size(); i++)
	{
		m_expeditions[i].~Expedition();
	}
	while (!m_playerHand.empty())
	{
		m_playerHand.pop_back();
	}

}


void Player::SortHand()
{
	std::sort(m_playerHand.begin(), m_playerHand.end());
}
void Player::PlaceCardInPlayerHand(Card card, int index)
{
	m_playerHand.insert(m_playerHand.begin() + index, card);
	SortHand();
}

void Player::AddCardToExpedition(int index)
{
	if (index < 0 && index >= m_expeditions.size())
		throw std::out_of_range("\nExpeditions are indexed from 1 to 5. Please choose a valid index.");
	Card playedCard(m_playerHand.at(index));
	if (m_expeditions.at((int)playedCard.GetColor()).CardsAreInAscendingOrder(playedCard))
	{
		playedCard = std::move(m_playerHand.at(index));
		m_expeditions.at((int)playedCard.GetColor()).GetPlayedCards().push_back(playedCard);
	}
	else throw("The card you want to insert does not respect the order.");
	m_playerHand.erase(m_playerHand.begin()+index);
	std::cout << '\n' << playedCard << "added\n";
	m_currentScore += m_expeditions[(int)playedCard.GetColor()].SetScore((int)playedCard.GetColor(), (int)playedCard.GetValue());

}

void Player::AddCardToDiscardPile(int index, std::stack<Card>& pile)
{
	if (index < 0 && index >= m_expeditions.size())
		throw std::out_of_range("Discard piles are indexed from 1 to 5. Please choose a valid discard pile.");
	Card playedCard(std::move(m_playerHand.at(index)));
	pile.push(playedCard);
	m_playerHand.erase(m_playerHand.begin() + index);
}

void Player::RemoveCardFromHand(int index)
{
	m_playerHand.erase(m_playerHand.begin()+index);
}

int16_t& Player::GetCurrentScore()
{
	return m_currentScore;
}

void Player::SetScore(int newScore)
{
	m_currentScore = newScore;
}

std::array<Expedition, 5> Player::GetExpeditions()
{
	return m_expeditions;
}

void Player::ResetPlayer()
{
	for (int i = 0; i < m_expeditions.size(); i++)
	{
		m_expeditions[i].ResetExpedition();
	}
	while (!m_playerHand.empty())
	{
		m_playerHand.pop_back();
	}

}

void Player::PrintCurrentScore()
{
	std::cout <<"\n"<< m_name << "'s score is " << m_currentScore << "\n";
}

void Player::SetTotalScore()
{
	uint16_t scoreSum = 0;
	for (auto i = 0; i < m_expeditions.size(); i++)
		scoreSum += m_expeditions[i].GetScore();
	m_currentScore = scoreSum;
}

void Player::SetName(const std::string& chosenName)
{
	m_name = chosenName;
}

void Player::PrintExpeditionScores()
{
	for (int index = 0; index < 5; index++)
		std::cout <<'\n'<< m_expeditions[index].GetScore()<<' ';
}

std::string Player::GetPlayerName()
{
	return m_name;
}

std::vector<Card>& Player::GetPlayerHand()
{
	return m_playerHand;
}
std::ostream& operator<<(std::ostream& out, const Player& player)
{
	for (int i = 0; i < player.m_playerHand.size(); i++)
		out << (int)player.m_playerHand[i].GetValue() << "  ";
	out << "\n";
	for (int i = 0; i < player.m_playerHand.size(); i++)
		switch (player.m_playerHand[i].GetColor())
		{
		case Card::Colour::gold:
			out << "GO ";
			break;
		case Card::Colour::blue:
			out << "BL ";
			break;
		case Card::Colour::white:
			out << "WH ";
			break;
		case Card::Colour::green:
			out << "GR ";
			break;
		case Card::Colour::red:
			out << "RE ";
			break;
		default:
			break;
		}
	return out;
}
void Player::PrintCurrentHand()
{
	for (int index = 0; index < m_playerHand.size(); index++)
		std::cout <<'\n'<<index+1<<"-> "<< m_playerHand[index] << " ";
	std::cout << '\n';
}
