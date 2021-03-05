#include "Game.h"
// for forward declaration of lobby
#include"Lobby.h"


game::game()
{
	create_deck();
	create_dealer();
}

void game::sleep(USHORT seconds)
{
	boost::this_thread::sleep_for(boost::chrono::seconds(seconds));
}

void game::get_bets()
{
	for (auto p : players)
	{
		p->get_bet();
	}
}
int game::get_num_players()
{
	return players.size();
}

bool game::play_again(player_ptr p)
{
	p->write("Would you like to play again?  (y)es or (N)o");
	std::string input = p->read();
	switch (input[0])
	{
	default:
		play_again(p);
		break;
	case ('n'):
		return false;
		break;

	case ('y'):
		return true;
		break;
	}
}

void game::hit_or_stick(player_ptr p)
{
		p->write("(H)it or (S)tick");
		std::string input = p->read();
		switch (input[0])
		{
		default:
			p->write("Please enter correct command");
			break;
		case('s'):
			//stick(p);
			break;
		case('S'):
			//stick(p);
			break;
		case('h'):
			hit(p);
			break;
		case('H'):
			hit(p);
			break;
		}
}

void game::hit(player_ptr current_player)
{
	current_player->take_card(deck_);
	current_player->show_cards();
	if(current_player->get_hand_value() < 21
			&& current_player->get_number_of_cards() < 5)
	{
		hit_or_stick(current_player);
	}	
}

void game::stick(player_ptr current_player)
{
	// DO nothing, waits till end round
}

void game::reset_player(player_ptr p)
{
	p->card_back_to_deck(deck_);
}

void game::reset_dealer()
{
	dealer_->card_back_to_deck(deck_);
}


void game::create_deck()
{
	std::shared_ptr<deck> new_deck(new deck());
	deck_ = (new_deck);

}

void game::create_dealer()
{
	std::cout << "dealer created\n";
	boost::shared_ptr<dealer> deal(new dealer("Dealer"));
	dealer_ = std::move(deal); 
}

void game::add_player(player_ptr player)
{
	players.insert(player);
}

void game::start_new_game(lobby* lobby_ptr)
{
	create_deck();
	dealer_->take_card(deck_);
	for (auto p : players) 
	{
		p->take_card(deck_);
		p->show_cards();
		get_bets();
	}
	for (auto p : players)
	{
		dealer_->take_card(deck_);
		p->take_card(deck_);
		p->show_cards();
		if (p->get_hand_value() < 21)
		{
			hit_or_stick(p);
		}
		end_round(p);
		if (play_again(p))
		{
			p->reset_hand();
			dealer_->reset_hand();
			start_new_game(lobby_ptr);
		}
		else 
		{
			lobby_ptr->insert_player(std::move(p));
			//p->leave();
		}
	}
}

void game::start_multiplayer_game(lobby* lobby_ptr)
{
	create_deck();
	dealer_->take_card(deck_);
	for (auto p : players) 
	{
		p->take_card(deck_);
		p->show_cards();
	}
	get_bets();
	dealer_->take_card(deck_);

	for (auto p : players)
	{

		p->take_card(deck_);
		p->show_cards();
		if (p->get_hand_value() < 21)
		{
			hit_or_stick(p);
		}		
	}
	end_round();
	for (auto p : players) 
	{
		p->reset_hand();
		lobby_ptr->insert_player(std::move(p));
	}
	players.clear();
}
// end round single player
void game::end_round(player_ptr p)
{
	sleep(1);
	p->write("Dealer Cards : " + dealer_->show_hand() + "#");
	int player_val = p->get_hand_value();
	int dealer_val = dealer_->get_hand_value();
	if (player_val <= 21)
	{
		while (dealer_val < player_val &&
			dealer_->get_number_of_cards() < 5)
		{
			sleep(1);
			dealer_->take_card(deck_);
			p->write("Dealer Cards : " + dealer_->show_hand() + "#");
			dealer_val = dealer_->get_hand_value();
		}
		if (player_val <= dealer_val && dealer_val <=21)
		{
			sleep(1);
			p->inc_games_lost();
			p->write("Dealer Wins#");
		}
		else
		{
			sleep(1);
			p->inc_games_won();
			p->write("Player Wins#");
			p->set_balance(p->get_bet_amount() * 2);
		}
	}
	else
	{
		p->inc_games_lost();
		sleep(1);
		p->write("Dealers Cards " + dealer_->show_hand() + "#");
		p->write("Dealer Wins#");
	}
	p->inc_games_played();

}
// end round multiplayer
void game::end_round()
{
	for (auto p : players)
	{
		p->write("Dealers Hand " + dealer_->show_hand() + "#");
	}
	int dealer_val = dealer_->get_hand_value();
	for (auto p : players) {
		int player_val = p->get_hand_value();
		if (player_val <= 21)
		{
			while (dealer_val < player_val &&
				dealer_->get_number_of_cards() < 5)
			{
				dealer_->take_card(deck_);
				sleep(1);
				p->write("Dealer Cards : " + dealer_->show_hand() + "#");
				dealer_val = dealer_->get_hand_value();
			}
			for (auto p : players) 
			{
				p->write("Dealer Cards : " + dealer_->show_hand() + "#");
			}
			if (player_val <= dealer_val && dealer_val <= 21)
			{
				sleep(1);
				p->write("Dealer Wins#");
				p->inc_games_lost();
			}
			else
			{
				sleep(1);
				p->inc_games_won();
				p->write("Player Wins#");
				p->set_balance(p->get_bet_amount() * 2);

			}
		}
		else
		{
			sleep(1);
			p->write("Dealers Cards " + dealer_->show_hand() + "#");
			p->write("Dealer Wins#");
			p->inc_games_lost();
		}
	}
	for (auto p : players) 
	{
		p->inc_games_played();
		p->write("Ending game .... #");
	}
}


