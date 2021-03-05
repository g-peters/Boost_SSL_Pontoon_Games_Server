#pragma once
#include "Card.h"
#include "Deck.h"
#include <vector>
#include <fstream>
#include <deque>

#include <string>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/filesystem.hpp>

typedef boost::asio::ip::tcp::socket bsock;
typedef boost::asio::ssl::stream <bsock> ssl_socket;
typedef std::unique_ptr<bsock> sock_ptr;
typedef std::unique_ptr<ssl_socket> ssl_sock_ptr;
typedef std::shared_ptr<card> card_ptr;
typedef unsigned short int USHORT;

constexpr int min_bet = 0;
constexpr int max_bet = 200;

class player : public std::enable_shared_from_this<player>
{
private:
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& games_played;
		ar& games_won;
		ar& games_lost;
		ar& balance;
	}
	unsigned short int bet_amount;
	unsigned int games_played;
	unsigned int games_won;
	unsigned int games_lost;
	unsigned int balance;
	//std::deque<card> player_cards;
	ssl_sock_ptr sock;
	boost::asio::streambuf buffer;
	bool ready;
	unsigned short int number_of_cards;
	bool win;
	bool logged_in;
	void login();
	void create_user(std::string, std::string);
	bool check_login(std::string,std::string);
	void load_data();
protected:

	std::deque<card_ptr> player_cards;
	std::string player_name;
	USHORT hand_value;
public:
	void save_data();
	void reset_hand();
	void leave();
	void inc_games_won();
	void inc_games_lost();
	void inc_games_played();
	void print_stats();
	USHORT get_bet_amount();
	bool get_win();
	virtual void get_bet();
	int get_hand_value();
	bool get_ready();
	void set_balance(int);
	int get_balance();
	virtual std::string read();
	virtual void show_cards();
	void get_name();
	void card_back_to_deck(std::shared_ptr<deck>);
	void take_card(std::shared_ptr<deck>);
	virtual void write(std::string);
	USHORT get_number_of_cards();
	std::string get_input();
	// new player ctor
	player(ssl_sock_ptr&);
	// dealer/server  ctor, no need for socket
	player(std::string); // for server side player(dealer), doesnt need a socket
	player() {}
	virtual ~player();

	};

