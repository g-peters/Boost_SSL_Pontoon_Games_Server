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
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include "Dealer.h"

typedef boost::shared_ptr<player> player_ptr;
typedef boost::shared_ptr<dealer> dealer_ptr;



class game
{
private:
	boost::shared_ptr<dealer> dealer_;
	void sleep(USHORT);
	void get_bets();
	bool play_again(player_ptr);
	void hit_or_stick(player_ptr);
	USHORT deck_number;
	std::shared_ptr<deck> deck_;
	std::set<player_ptr> players;
	std::set<player_ptr> temp_players;
	std::set<player_ptr> players_leaving;
	void hit(player_ptr);
	void stick(player_ptr);

public:
	int num_of_players();
	void reset_player(player_ptr);
	void reset_dealer();
	game();
	void create_deck();
	void create_dealer();
	void add_player(player_ptr player);
	void start_new_game();
	void end_round();
};

