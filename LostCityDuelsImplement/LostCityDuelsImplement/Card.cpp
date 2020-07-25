#include "Card.h"


Card::Card()
{
	m_colors = Colour::none;
	m_values = CardValues::none;
}

Card::Card(const Colour& assignedColor, const CardValues& assignedValue)
{
	m_colors = assignedColor;
	m_values = assignedValue;
}

Card::Card(Card&& other) noexcept
{
	this->m_colors = other.m_colors;
	this->m_values = other.m_values;
	new(&other) Card;
}

bool Card::operator<(const Card& card2)
{
	if (this->GetColor() == card2.GetColor())
	{
		return this->GetValue() < card2.GetValue();
	}
	return this->GetColor() < card2.GetColor();
}


Card Card::operator=(const Card& secondCard)
{
	if (this == &secondCard)
		return *this;
	m_colors = secondCard.m_colors;
	m_values = secondCard.m_values;
	return *this;
}

Card Card::operator=(Card&& other) noexcept
{
	m_values = other.m_values;
	m_colors = other.m_colors;

	new(&other)Card;

	return *this;
}


Card::Card(const Card& secondCard)
{
	m_colors = secondCard.m_colors;
	m_values = secondCard.m_values;
}

Card::CardValues Card::GetValue() const
{
	return m_values;
}

Card::Colour Card::GetColor() const
{
	return m_colors;
}

std::string Card::GetCardColourString()
{
	if ((int)m_colors == 0)
		return "gold";
	if ((int)m_colors == 1)
		return "blue";
	if ((int)m_colors == 2)
		return "white";
	if ((int)m_colors == 3)
		return "green";
	if ((int)m_colors == 4)
		return "red";
}

std::string Card::GetCardValueString()
{
	if ((int)m_values == 1)
		return "$";
	if ((int)m_values == 2)
		return "2";
	if ((int)m_values == 3)
		return "3";
	if ((int)m_values == 4)
		return "4";
	if ((int)m_values == 5)
		return "5";
	if ((int)m_values == 6)
		return "6";
	if ((int)m_values == 7)
		return "7";
	if ((int)m_values == 8)
		return "8";
	if ((int)m_values == 9)
		return "9";
	if ((int)m_values == 10)
		return "10";
}

std::ostream& operator<<(std::ostream& flux,const Card& card)
{
	switch (card.m_colors)
	{
	case Card::Colour::gold:
		flux << "Go ";
		break;
	case Card::Colour::blue:
		flux << "Bl ";
		break;
	case Card::Colour::white:
		flux << "Wh ";
		break;
	case Card::Colour::green:
		flux << "Gr ";
		break;
	case Card::Colour::red:
		flux << "Re ";
		break;
	default:
		break;
	}

	switch (card.m_values)
	{
	case Card::CardValues::investition:
		flux << " $ ";
		break;
	case Card::CardValues::secondCard:
		flux << " 2 ";
		break;
	case Card::CardValues::thirdCard:
		flux << " 3 ";
		break;
	case Card::CardValues::fourthCard:
		flux << " 4 ";
		break;
	case Card::CardValues::fifthCard:
		flux << " 5 ";
		break;
	case Card::CardValues::sixthCard:
		flux << " 6 ";
		break;
	case Card::CardValues::seventhCard:
		flux << " 7 ";
		break;
	case Card::CardValues::eighthCard:
		flux << " 8 ";
		break;
	case Card::CardValues::ninthCard:
		flux << " 9 ";
		break;
	case Card::CardValues::tenthCard:
		flux << "10 ";
		break;
	default:
		break;
	}
	return flux;
}

bool operator==(const Card& card1, const Card& card2)
{
	return (card1.GetColor() == card2.GetColor() && card1.GetValue() == card2.GetValue());
}

