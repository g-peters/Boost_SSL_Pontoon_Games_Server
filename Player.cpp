#include "Player.h"

void player::show_cards()
{
	std::string card_hand = "";
	for (int i = 0; i < player_cards.size(); ++i) {
		if (i > 0) {
			card_hand += ", ";
		}
		card_hand += player_cards[i]->get_face() + " ";
		card_hand += player_cards[i]->get_suit();
	}
	int value = get_hand_value();
	write("Your cards : " + card_hand + " (" + std::to_string(value) + ")" +  '#');
}

void player::card_back_to_deck(std::shared_ptr<deck> deck)
{
	for(int i = 0; i <= player_cards.size();++i)
	{
		// move card back to deck
		deck->return_card_to_deck(std::move(player_cards[i]));
		//remove card from players hand
		if (!player_cards.empty()) {
			player_cards.pop_front();
		}
	}
}

void player::take_card(std::shared_ptr<deck> deck)
{	// take card from top of deck
	player_cards.push_back(std::move(deck->get_card()));
}

player::player(std::string name): win(0)
{
	player_name = name; // dealer
}

void player::get_name()
{
	write("Enter your name.\n");
	player_name = read();
}

player::player(ssl_sock_ptr& s) : sock(std::move(s)), balance(1000)
{
	std::cout << "Player connected to server: " << player_name << std::endl;
}

void player::reset_hand()
{
	player_cards.clear();
}

void player::leave()
{
	try
	{
		write("exit");
		sock->shutdown();
	}
	catch(std::exception& e)
	{
		//Receives EOF error which is expected with SSL socket shutdown
		// https://stackoverflow.com/questions/25587403/boost-asio-ssl-async-shutdown-always-finishes-with-an-error ( Tanner Sansbury )
		//std::cout << "Error in player leave : " << e.what();
	}
}

USHORT player::get_bet_amount()
{
	return bet_amount;
}

bool player::get_win()
{
	return win;
}

void player::get_bet()
{
	write("Enter your Bet (0 - 200)");
	std::string bet_string = "";
	bet_string = read();
	std::cout << "Bet Amount " << bet_string << std::endl;

	bool is_only_int = (bet_string.find_first_not_of("0123456789") == std::string::npos);
	if (!is_only_int) {
		get_bet();
	}

	
	try {
		std::cout << "content of bet string " << bet_string << std::endl;
		int bet = std::stoi(bet_string);
		bet_string = "";


		std::cout << "value of bet is now : " << bet << std::endl;
		if (bet < min_bet || bet > max_bet)
		{
			write("Please enter a correct bet amount.#");
			get_bet();
		}
		if (bet > balance) {
			write("You do not have enough coins for that bet#");
			get_bet();
		}

		bet_amount = bet;
	}
	catch (std::exception& e) { std::cout << "Exception STOI :" << e.what(); }
}

int player::get_hand_value()
{
	int sum_of_hand = 0;
	bool contains_ace = false;
	for (auto card : player_cards) 
	{
		if(card->get_face() == "ACE")
		{
			contains_ace = true;
		}
		sum_of_hand += card->get_value();

	}
	if (sum_of_hand <= 11 && contains_ace == true) {
		sum_of_hand += 10;
	}
	return sum_of_hand;
}

bool player::get_ready()
{
	return ready;
}

void player::set_balance(int num)
{
	balance += num;
}

int player::get_balance()
{
	return balance;
}

std::string player::read()
{
	boost::asio::read_until(*sock, buffer, "\n");
	std::istream is(&buffer);
	std::string line;
	std::getline(is, line);
	buffer.consume(line.size());
	return line;
}

void player::write(std::string data)
{
	try 
	{
		boost::asio::write(*sock, boost::asio::buffer(data + "\n"));
		//buffer.consume(data.size());
	}
	catch (std::exception& e) 
	{
		std::cout << "Error in player write "<< e.what();
	}
}

USHORT player::get_number_of_cards()
{
	return player_cards.size();
}

std::string player::get_input()
{
	std::string data;
	std::getline(std::cin, data);
	return data;
}

player::~player()
{
	std::cout << "Player Left (DTOR)\n";
}