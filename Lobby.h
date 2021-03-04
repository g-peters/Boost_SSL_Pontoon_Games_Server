#pragma once

#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>
#include "Player.h"
#include "Dealer.h"
#include <vector>
#include <memory>
#include <string> // std::stoi
#include "Game.h"
#include <set>
#include <queue>
#include <iostream>

typedef boost::shared_ptr<player> player_ptr;
typedef boost::shared_ptr<dealer> dealer_ptr;

class lobby : public std::enable_shared_from_this<lobby>
{
public:
	lobby(); 
	~lobby();
	void insert_player(player_ptr);
private:
	void main_menu(player_ptr);
	void single_or_multi(player_ptr);
	std::queue<player_ptr> multiplayer_queue;
	std::vector<player_ptr> player_vec;
	unsigned short int multiplayer_size;
	game *multi_game;
	void remove_player(player_ptr);
	void singleplayer(player_ptr);
	void multiplayer(unsigned short int);

};

