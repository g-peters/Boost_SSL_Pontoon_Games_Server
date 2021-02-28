#pragma once

#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>
#include "Player.h"
#include "Dealer.h"
#include <memory>
#include "Game.h"
#include <set>
#include <iostream>
#include <string> // std::to_string
typedef boost::shared_ptr<player> player_ptr;
typedef boost::shared_ptr<dealer> dealer_ptr;
class lobby
{
public:
	lobby(); 
	void insert_player(player_ptr);

private:
	std::vector<bool> all_ready;
	game multiplayer_game;
	unsigned short int num_of_multiplayers;
	void choose_single_or_multiplayer(player_ptr);
	void remove_player(player_ptr);
	void singleplayer(player_ptr);
	void multiplayer(player_ptr);
	std::vector<player_ptr> vec_players;
};

