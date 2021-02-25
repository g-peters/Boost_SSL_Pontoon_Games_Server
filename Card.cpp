#include "Card.h"

void card::assign_value()
{
	if (face > 9) 
	{ 
		value = 10; 
	}
	else value = face + 1;

}

card::card(int f, int s) : suit(s), face(f) {
	assign_value(); // constructor
	fill_map_face();
	fill_map_suit();
}



card::card(const card& old)
{
	value = old.value;
	suit = old.suit;
	face = old.face;
	card_face = old.card_face;
	suits = old.suits;
}

card::card(const card&& old)
{
	value = old.value;
	suit = old.suit;
	face = old.face;
	card_face = old.card_face;
	suits = old.suits;
}

std::string card::get_suit()
{
	return suits[suit];
}

std::string card::get_face()
{
	return card_face[face];
}


int card::get_value()
{
	return value;
}
void card::fill_map_face()
{
	card_face[0] = "ACE";
	card_face[1] = "TWO";
	card_face[2] = "THREE";
	card_face[3] = "FOUR";
	card_face[4] = "FIVE";
	card_face[5] = "SIX";
	card_face[6] = "SEVEN";
	card_face[7] = "EIGHT";
	card_face[8] = "NINE";
	card_face[9] = "TEN";
	card_face[10] = "JACK";
	card_face[11] = "QUEEN";
	card_face[12] = "KING";

}

void card::fill_map_suit()
{
	suits[0] = "SPADES";
	suits[1] = "CLUBS";
	suits[2] = "HEARTS";
	suits[3] = "DIAMONDS";


}
