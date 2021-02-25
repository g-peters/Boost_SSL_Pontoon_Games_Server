#pragma once

#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>
#include "Player.h"
#include "Dealer.h"
#include <memory>
#include "Game.h"
#include <set>
#include <iostream>

typedef boost::shared_ptr<player> player_ptr;
typedef boost::shared_ptr<dealer> dealer_ptr;
class lobby
{
public:
	lobby() {}
	void insert_player(player_ptr);
private:
	
	void remove_player(player_ptr);
	void singleplayer(player_ptr);
};

