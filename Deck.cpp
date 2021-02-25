#include "Deck.h"
#include <iostream>
deck::deck() {// constructor

	create_deck();
	shuffle();
	//print_deck(); for debug purposes
}


void deck::shuffle()

{
	std::srand(unsigned(std::time(0)));
	std::cout << "shuffling the deck ... \n\n\n";
	std::random_shuffle(deck_cards.begin(), deck_cards.end());


}

void deck::print_deck()
{
	std::cout << "\n\n";
	for (int i = 0; i < deck_cards.size(); ++i)
	{
		deck_cards[i]->get_face();
		deck_cards[i]->get_suit();
		deck_cards[i]->get_value();

		std::cout << "\n";
	}std::cout << "size of deck is " << deck_cards.size();
	std::cout << "\n\n\n";
}




std::deque<card_ptr> deck::deck_of_cards()
{
	return deck_cards;
}

void deck::create_deck()
{
	std::cout << "deck created" << std::endl;
	for (int i = 0; i < 13; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			//deck_cards.push_back(new card(i, j));
			card_ptr c (new card(i, j));
			deck_cards.push_back(c);
		}
	}
}

card_ptr deck::get_card()
{
	inplay_cards.push_back(std::move(deck_cards[top_of_deck]));
	deck_cards.pop_front();
	return inplay_cards.back();

}

void deck::return_card_to_deck(card_ptr card_)
{
	deck_cards.push_back(card_);
	
}
