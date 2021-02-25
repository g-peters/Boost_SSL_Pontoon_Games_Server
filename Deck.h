#pragma once
#include <deque>
#include "Card.h"
#include <map>
#include <vector>
#include <memory>
#include <algorithm>  // random_shuffle
#include <ctime> //srand seeding
//#define TOP_OF_DECK 0;
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

