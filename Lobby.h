#pragma once

#include <boost/asio.hpp>
#include "Player.h"
#include <memory>
#include "Game.h"
#include <set>
#include <iostream>

typedef std::shared_ptr<player> player_ptr;

class lobby
{
public:
	lobby() {}
	void insert_player(player_ptr);
private:
	
	void remove_player(player_ptr);
	void singleplayer(player_ptr);
};

