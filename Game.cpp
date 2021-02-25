#include "Game.h"

void game::sleep(USHORT seconds)
{
	boost::this_thread::sleep_for(boost::chrono::seconds(seconds));
}

void game::take_cards(int deck)
{	
	dealer_->take_card(vec_decks[deck - 1]);
	for (auto player : players)
	{
		player->take_card(vec_decks[deck - 1]);
	}
}

void game::show_cards()
{
	dealer_->player_show_cards();
	for (auto p : players)
	{
		p->player_show_cards();
	}
}

void game::get_bets()
{
	for (auto p : players)
	{
		p->get_bet();
	}
}

void game::check_winner()
{
	if (dealer_->get_hand_value() == 21) {
		winner = false; // dealer has pontoon / dealer wins incase of draw
					    
	}
	else
	{
		for (auto player : players)
		{
			int val = player->get_hand_value();
			if (val == 21 && player->get_number_of_cards() < 5) {
				winner = true;
			}
			else if (player->get_hand_value() > dealer_->get_hand_value()) {
				winner = true;
			}
		}
	}
}

void game::end_game(player_ptr player)
{
	player->write("Would you like to play again?");

	std::string input = player->read();
	if (input == "y")
	{
		for (int i = 0; i <= player->get_number_of_cards(); ++i)
		{
			player->card_back_to_deck(vec_decks[0]);
		}
		for (int i = 0; i <= dealer_->get_number_of_cards(); ++i)
		{
			dealer_->card_back_to_deck(vec_decks[0]);
		}
		play(0);
	}
	else
	{
		player->write("Thanks for playing#");
		player->write("Exiting Game ...#");
		sleep(1);
		player->leave();
		players.erase(player);
	}
}

void game::end_round()
{
}

void game::options()
{
	for (auto p : players)
	{
		while (p->get_hand_value() < 21) {
			std::string input = "";
			// stick or twist
			p->write("Hit or Stick");
			input = p->read();

			if (input == "stick")
			{
				//std::string dealer_Cards = dealer_->show_hand();
				p->write("Dealers Cards : " + dealer_->show_hand() + "#");
				dealer_turn(p);
			}
			else if (input == "hit")
			{
				p->take_card(vec_decks[deck_number]);
				p->player_show_cards();
				if (p->get_hand_value() > 21)
				{
					
					p->write("Bust!!#");
					p->write("Dealers hand : " + dealer_->show_hand() + "#");
					p->write("Dealer Wins#");
					end_game(p);

				}
				else if(p->get_hand_value() == 21)
				{
					dealer_turn(p);
				}
			}
			else
			{
				p->write("Please enter correct command");
				input = p->read();
			}
		}
	}
}

void game::dealer_turn(player_ptr player)
{
	player->write("Dealer turn #");
	sleep(1);

	while (dealer_->get_hand_value() <= player->get_hand_value()
									&& dealer_->get_hand_value() < 21)
	{
		dealer_->take_card(vec_decks[deck_number]);
		sleep(1);
		player->write("Dealer takes card : " + dealer_->show_hand() + "#");
		if(dealer_->get_hand_value() >21 && player->get_hand_value() <= 21)
		{
			player->write("You win!#");
			end_game(player);

		}
		else
		{
			player->write("Dealer Wins#");
			end_game(player);
		}
	}
	player->write("Dealer Wins#");
	end_game(player);
}

game::game() : winner(false)
{
	create_deck();
	create_dealer();
}

void game::create_deck()
{
	std::shared_ptr<deck> new_deck(new deck());
	vec_decks.push_back(new_deck);

}

void game::create_dealer()
{
	std::cout << "Dealer Created\n";
	boost::shared_ptr<dealer> deal(new dealer("Dealer"));
	dealer_ = std::move(deal); 
}

void game::add_player(player_ptr player)
{
	
	players.insert(std::move(player));
	std::cout << "Player added to game Instance\n";
}

void game::play(int deck_no)
{
	deck_number = deck_no;
	bool game_over = false;
	dealer_->take_card(vec_decks[deck_number]);
	for (auto p : players)
	{
		p->take_card(vec_decks[deck_number]);
		p->player_show_cards();
		get_bets();
	}
	dealer_->take_card(vec_decks[deck_number]);
	for (auto p : players)
	{
		p->take_card(vec_decks[deck_number]);
		p->player_show_cards();
		options();

	}
}
game::~game(){
	std::cout << "GAME DTOR called\n";
}