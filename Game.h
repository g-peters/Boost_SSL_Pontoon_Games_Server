#pragma once
//#include "lobby.h"
#include <vector>
#include <map>
#include <memory>
#include "Card.h"
#include "Deck.h"
#include <deque>
#include <vector>
#include "Player.h"
#include <set>
#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include "Dealer.h"

typedef boost::shared_ptr<player> player_ptr;
typedef boost::shared_ptr<dealer> dealer_ptr;

class lobby; // forward declaration for lobby_ptr
class game
{
private:
	boost::shared_ptr<dealer> dealer_;
	void get_bets();
	bool play_again(player_ptr);
	void hit_or_stick(player_ptr);
	USHORT deck_number;
	std::shared_ptr<deck> deck_;
	std::set<player_ptr> players;
	void hit(player_ptr);
	void stick(player_ptr);

public:
	static void sleep(USHORT);
	int get_num_players();
	void reset_player(player_ptr);
	void reset_dealer();
	game();
	void create_deck();
	void create_dealer();
	void add_player(player_ptr player);
	void start_new_game(lobby* lobby_ptr);
	void start_multiplayer_game(lobby*);
	void end_round();
	void end_round(player_ptr);
};

