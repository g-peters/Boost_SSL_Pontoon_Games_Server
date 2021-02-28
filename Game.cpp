#include "Game.h"

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
	current_player->write("Dealers Hand " + dealer_->show_hand() + "#");
	int playerValue = current_player->get_hand_value();
	int bankValue = dealer_->get_hand_value();

	while(dealer_->get_hand_value() < 21 
			&& dealer_->get_hand_value() < current_player->get_hand_value()
			&& dealer_->get_number_of_cards() < 5)
	{
		sleep(1);
		dealer_->take_card(deck_);
		current_player->write("Dealers Hand " + dealer_->show_hand() + "#");
	}


}

void game::reset_player(player_ptr p)
{
	p->card_back_to_deck(deck_);
}

void game::reset_dealer()
{
	dealer_->card_back_to_deck(deck_);
}

game::game()
{
	std::cout << "game created\n";
	//create_deck();
	create_dealer();
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
	std::cout << "player added\n";
	players.insert(player);
}
int game::num_of_players()
{
	return players.size();
}

void game::start_new_game()
{
	try{

	create_deck();
	//dealer_->card_back_to_deck(deck_);
	dealer_->take_card(deck_);
	for (auto p : players) 
	{
		p->take_card(deck_);
		p->show_cards();
		//get_bets();
	}
	/////////////////////////////////////
	dealer_->take_card(deck_);

	for (auto p : players)
	{
		p->take_card(deck_);
		p->show_cards();
		if (p->get_hand_value() < 21)
		{
			hit_or_stick(p);
		}
	}//////////////////////////////////////
	end_round();
	

	for(auto p : players)
	{		
		if( play_again(p))
		{
			std::cout << "Player chose to play again\n";
			sleep(1);
			std::cout << "2 ::: \n";
			p->reset_hand();
			// move players that want to play again into temp container
			temp_players.insert(p);
		}
		else
		{
			std::cout << "Player chose to leave\n";
			players_leaving.insert(p);
		}
	}//////////////////////////////////////
	// empty current set of players
	std::cout << "Emptying player set " << players.size() << std::endl;
	players.clear();
	std::cout << " player set  emptied " << players.size() << std::endl;

	for (auto p : temp_players)
	{
		std::cout << "Temp players moved into\n";
		// move from temp container to play container
		players.insert(p);
	}/////////////////////////////////////
		std::cout << "Emptying temp set " << temp_players.size() << std::endl;

	temp_players.clear();

		std::cout << " temp set  emptied " << temp_players.size() << std::endl;

	for (auto p : players_leaving)
	{
		std::cout << "Removing players from leave set " << players_leaving.size() <<std::endl;
		// reset pointer, go out of scope, player DTOR will be called
	//	p.reset();
		p->leave();
	}///////////////////////////////////////
		std::cout << "Players leaving " << players_leaving.size() << std::endl;
	//players_leaving.clear();
	std::cout << "Players left " << players_leaving.size() << std::endl;

	
	std::cout << "PLAYERS SIZE BEFORE NEW GAME : " << players.size();
	if(players.size() > 0)
	{
		dealer_->reset_hand();
		start_new_game();
	}
	}
	catch(std::exception& e)
	{
		std::cout << "EXCEPT:: " << e.what() << std::endl;
	}
}

void game::end_round()
{
	for (auto p : players)
	{
	p->write("Dealers Cards : " + dealer_->show_hand() + "#");
	int player_val = p->get_hand_value();
	int dealer_val = dealer_->get_hand_value();
	if (player_val <= 21)
	{
		while (dealer_val < player_val &&
			dealer_->get_number_of_cards() < 5)
		{
			dealer_->take_card(deck_);
			p->write("Dealer Cards : " + dealer_->show_hand() + "#");
			dealer_val = dealer_->get_hand_value();
		}
		if (player_val <= dealer_val && dealer_val <=21)
		{
			p->write("Dealer Wins#");
		}
		else
		{
			p->write("Player Wins#");
		}
	}
	else
	{
		p->write("Dealers Cards " + dealer_->show_hand() + "#");
		p->write("Dealer Wins#");
	}
	}
}

