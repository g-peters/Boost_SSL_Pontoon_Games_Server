#pragma once

#include <vector>
#include <map>
#include <memory>
#include "Card.h"
#include "Deck.h"
#include <deque>
#include "Player.h"
#include <set>
#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>
#include "Deck.h"

typedef std::shared_ptr<player> player_ptr;


class game
{
private:
	
	std::vector<std::shared_ptr<deck>> vec_decks;
	std::set<player_ptr> players;
public:
	game();
	void create_deck();
	void create_dealer();
	void add_player(player_ptr player);
	void play(int); // needs the number of deck to be played on
};

