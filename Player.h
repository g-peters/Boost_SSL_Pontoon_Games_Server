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



class player : public std::enable_shared_from_this<player>
{
private:
	std::deque<card> player_cards;
	std::string player_name;
	//sock_ptr sock;
	ssl_sock_ptr sock;
	boost::asio::streambuf buffer;
	bool ready;
	//std::shared_ptr<deck> deck;
	int player_id;
public:
	//void set_deck(std::shared_ptr<deck>);
	bool get_ready();
	virtual std::string read();
	void player_show_cards();
	void get_name();
	void card_back_to_deck(card*);
	void take_card(std::shared_ptr<deck>);
	virtual void write(std::string);
	std::string get_input();
	// new player ctor
	player(ssl_sock_ptr&);
	// dealer/server  ctor, no need for socket
	player(std::string); // for server side player(dealer), doesnt need a socket
	~player();
	
	std::thread* t;
};

