#include "Player.h"

void player::player_show_cards()
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
	for(int i = 0; i < player_cards.size();++i)
	{
		// move card back to deck
		deck->return_card_to_deck(std::move(player_cards[i]));
		//remove card from players hand
		player_cards.pop_front();
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


void player::leave()
{
	try
	{
		boost::asio::error::eof;
		boost::system::error_code ec;

		std::cout << "LEAVE CALLED\n";
		write("exit");
		//sock->shutdown(ec);
		sock->lowest_layer().shutdown(
					boost::asio::ip::tcp::socket::shutdown_both, ec);
		//sock->lowest_layer().close(ec);

	}
	catch(std::exception& e)
	{
	
		std::cout << "Error in player leave : " << e.what();

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
	std::string bet = read();
	// Need to test for integer - isdigit loop 
	// error here when entering string
	if(std::stoi(bet) < min_bet || std::stoi(bet) > max_bet)
	{
		write("Please enter a correct bet amount.#");
		get_bet();
	}
	if (std::stoi(bet) > balance) {
		write("You do not have enough coins for that bet#");
		get_bet();
	}

	bet_amount = std::stoi(bet);
}

int player::get_hand_value()
{
	int hand_value = 0;
	// sum up value of all cards in player hand
	for (auto card_ : player_cards) {
		// if ace value of 11 will cause more than 21, sets ace to 1
		if(card_->get_value() == 1 &&
				hand_value + card_->get_value() < 11) 
		{
			hand_value += 11;
		}
		else
		{
			hand_value += card_->get_value();
		}
		
	}
	return hand_value;
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
	std::string line;
	try
	{
		boost::asio::read_until(*sock, buffer, "\n");
		std::istream is(&buffer);
		std::getline(is, line);
		buffer.consume(line.size());
	}
	catch(std::exception& e)
	{
		std::cout << "Exception in Player Read: "  << e.what() << std::endl;
	}
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
		std::cout << "Exception in Player Write : " << e.what() << std::endl;
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
	player_left();
}
void player::player_left(){
	std::cout << "Player Left / DTOR\n";
}