#pragma once

#include <vector>
#include <map>
#include "Card.h"
#include "Deck.h"
#include <deque>
#include "Player.h"
#include <utility> //pairs
#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>
typedef boost::asio::ip::tcp::socket bsock;
typedef std::unique_ptr<bsock> sock_ptr;
typedef boost::asio::ssl::stream <bsock> ssl_socket;
typedef std::unique_ptr<ssl_socket> ssl_sock_ptr;


using boost::asio::ip::tcp;


class game
{
private:
	std::deque<card*> deck_cards;
	std::vector<player> vec_players;
	deck deck_;
	deck* ptr_deck = &deck_;
	std::string player_name;
	void setup_players();
	void listen();
	bool game_started;
	std::vector < std::pair<player, sock_ptr>> vec_of_pairs;
	void start_game();
	int port;

public:
	game(boost::asio::io_context&, int);
	boost::asio::io_context context;
};

