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
	std::cout << "\n shuffling the deck ... \n\n\n";
	std::random_shuffle(vec_of_cards.begin(), vec_of_cards.end());


}

void deck::print_deck()
{
	std::cout << "\n\n";
	for (int i = 0; i < vec_of_cards.size(); ++i)
	{
		vec_of_cards[i]->get_face();
		vec_of_cards[i]->get_suit();
		vec_of_cards[i]->get_value();

		std::cout << "\n";
	}std::cout << "size of deck is " << vec_of_cards.size();
	std::cout << "\n\n\n";
}



int deck::get_deck()
{
	int decka = 6;
	return decka;
}

std::deque<card*> deck::deck_of_cards()
{
	return vec_of_cards;
}

void deck::create_deck()
{
	std::cout << "deck created" << std::endl;
	for (int i = 0; i < 13; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			vec_of_cards.push_back(new card(i, j));
		}

	}
}

card deck::get_card()
{
	cards_in_play.push_back(std::move(vec_of_cards[0]));
	vec_of_cards.pop_front();
	return *cards_in_play.back();

}
