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
#include "Deck.h"
#include "Dealer.h"

typedef boost::shared_ptr<player> player_ptr;
typedef boost::shared_ptr<dealer> dealer_ptr;



class game
{
private:
	boost::shared_ptr<dealer> dealer_;
	void sleep(USHORT);
	void take_cards(int);
	void show_cards();
	void get_bets();
	void check_winner();
	void end_game(player_ptr);
	void end_round();
	void options();
	void dealer_turn(player_ptr);
	USHORT deck_number;
	bool winner;
	dealer Dealer;
	std::vector<std::shared_ptr<deck>> vec_decks;
	std::set<player_ptr> players;
public:
	game();
	~game();
	void create_deck();
	void create_dealer();
	void add_player(player_ptr player);
	void play(int); // needs the number of deck to be played on
};

