#pragma once
#include <deque> /* seems very well suited to a deck of cards
					as deque seems suited to operation on both ends
					e.g. taking cards off top of deck and when finished
					adding to the bottom
				 */
#include "Card.h"
#include <map>
#include <vector>
#include <algorithm>  // random_shuffle
#include <ctime> //srand seeding
class deck
{
private:
	std::deque<card*> vec_of_cards; // deck of 52 cards
	std::deque<card*> cards_in_play;
public:
	void shuffle();
	void print_deck();
	int get_deck();
	std::deque<card*> deck_of_cards();
	void create_deck();
	card get_card();
	deck();

};

