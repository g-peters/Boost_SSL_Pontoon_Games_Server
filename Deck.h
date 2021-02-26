#pragma once
#include <deque>
#include "Card.h"
#include <vector>
#include <algorithm>  // random_shuffle
#include <ctime> //srand seeding
#include <memory> // shared_ptr
static const unsigned short int  top_of_deck  = 0;
typedef std::shared_ptr<card> card_ptr;
class deck
{
private:
	std::deque<card_ptr>deck_cards;
	std::deque<card_ptr>inplay_cards;

public:
	void shuffle();
	void print_deck();
	std::deque<card_ptr> deck_of_cards();
	void create_deck();
	card_ptr get_card();
	void return_card_to_deck(card_ptr);
	deck();

};

