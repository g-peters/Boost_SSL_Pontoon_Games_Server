#pragma once
#include "Card.h"
#include "Deck.h"
#include <vector>
#include <deque>
#include <string>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

typedef boost::asio::ip::tcp::socket bsock;
typedef boost::asio::ssl::stream <bsock> ssl_socket;
typedef std::unique_ptr<bsock> sock_ptr;
typedef std::unique_ptr<ssl_socket> ssl_sock_ptr;



class player
{
private:
	std::deque<card> player_cards;
	std::string player_name;
	//sock_ptr sock;
	ssl_sock_ptr sock;
	//std::vector<char> buff;
	//boost::asio::streambuf buff;

public:
	void read();
	void player_show_cards();
	void card_back_to_deck(card*);
	void take_card(deck*);
	// new player ctor
	player(std::deque<card*>, deck*, ssl_sock_ptr&);
	// dealer/server  ctor, no need for socket
	player(std::string, std::deque<card*>, deck*); // for server side player(dealer), doesnt need a socket
	void get_name();
};

