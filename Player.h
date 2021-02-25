#pragma once
#include "Card.h"
#include "Deck.h"
#include <vector>
#include <deque>
#include <string>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <memory>
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
		USHORT bet_amount;
		//std::deque<card> player_cards;
		ssl_sock_ptr sock;
		boost::asio::streambuf buffer;
		bool ready;
		unsigned int balance;
		USHORT number_of_cards;
		bool win;
	protected:
		//std::deque<card> player_cards;
		std::deque<card_ptr> player_cards;
		std::string player_name;
		USHORT hand_value;
		




	public:
		void leave();
		USHORT get_bet_amount();
		bool get_win();
		virtual void get_bet();
		int get_hand_value();
		bool get_ready();
		void set_balance(int);
		int get_balance();
		virtual std::string read();
		virtual void player_show_cards();
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
		~player();
		virtual void player_left();
		std::thread* t;
	};

