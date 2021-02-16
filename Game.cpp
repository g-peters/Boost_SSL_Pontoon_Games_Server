#include "Game.h"

game::game()
{
	create_deck();
}

void game::create_deck()
{
	std::shared_ptr<deck> new_deck(new deck());
	vec_decks.push_back(new_deck);

}

void game::create_dealer()
{
	std::shared_ptr<player> dealer(new player("Dealer"));
	players.insert(dealer);
}

void game::add_player(player_ptr player)
{
	players.insert(player);
}

void game::play(int deck_number)
{
	std::cout << "Game: PLAY \n";
	for (int i = 0; i < 2; ++i) { // deals 2 cards each
		for (auto player : players)
		{
			player->take_card(vec_decks[deck_number - 1]);
			
		}
	}
}
