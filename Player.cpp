#include "Player.h"
#include "Game.h"
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

player::player(std::string name) 
{
	player_name = name; // dealer
}


void player::get_name()
{
	write("Enter your name.\n");
	player_name = read();
}

player::player(ssl_sock_ptr& s) : sock(std::move(s)), balance(1000),games_lost(0), games_won(0), games_played(0)
{
	login();
}

void player::login()
{
	std::string username, password;
	write("1: Login#");
	write("2: Register#");
	write("3: Continue as Guest");
	std::string input = read();
	switch (input[0])
	{
	default: login();
		break;
	case ('1'):
		write("Enter username");
		username = read();
		player_name = username;
		write("Enter Password");
		password = read();
		// check exists
		if (check_login(username, password)) 
		{
			write("Login Successfull#");
			logged_in = true;
			load_data();
		}
		else 
		{
			write("Login Unsuccessful#");
			login();
		}
		break;
	case ('2'):
		write("Create username");
		username = read();
		player_name = username;
		write("Create Password");
		password = read();
		create_user(username,password);
		logged_in = true;
		break;
	case ('3'):
		write("enter name");
		player_name = read();
		break;
	}
}

void player::create_user(std::string u_name, std::string pwd)
{
	std::hash<std::string> hash_string;
	std::ofstream ofs;
	ofs.open("users.txt", std::ios::app);
	ofs << u_name <<" " << hash_string(pwd) << std::endl;
	ofs.close();

}

bool player::check_login(std::string u_name, std::string pwd)
{
	bool found = false;
	std::ifstream password_file;
	std::hash<std::string> hash_string;
	password_file.open("users.txt");

	std::string stored_password, line, stored_username;
	std::stringstream iss(line);
	while (std::getline(password_file, line)) {

		std::stringstream iss(line);
		iss >> stored_username >> stored_password;

		if (u_name == stored_username) 
		{
			if(hash_string(pwd) == std::stoll(stored_password))
			{
				password_file.close();
				found = true;
			}
		}
	}
	password_file.close();
	return found;
}

void player::save_data()
{
	if (logged_in) 
	{
		std::ofstream file{ player_name + ".txt" };
		boost::archive::text_oarchive oa{ file };
		oa << games_played << games_won << games_lost << balance;
		file.close();
	}
}

void player::load_data()
{
	std::cout << "Loading data\n";
	if (boost::filesystem::exists(player_name + ".txt")) {
		std::ifstream file{ player_name + ".txt" };
		boost::archive::text_iarchive ia{ file };
		ia >> games_played >> games_won >> games_lost >> balance;
	}
}

void player::reset_hand()
{
	player_cards.clear();
}

void player::leave()
{
	try
	{
		write("Exiting Game .... #");
		game::sleep(1);
		write("exit_game");
		sock->shutdown();
	}
	catch(std::exception& e)
	{
		//Receives EOF error which is expected with SSL socket shutdown
		// https://stackoverflow.com/questions/25587403/boost-asio-ssl-async-shutdown-always-finishes-with-an-error ( Tanner Sansbury )
		//std::cout << "Error in player leave : " << e.what();
	}
}

void player::inc_games_won()
{
	++games_won;
}

void player::inc_games_lost()
{
	++games_lost;
}

void player::inc_games_played()
{
	++games_played;
}

void player::print_stats()
{
	write("Games Played: " + std::to_string(games_played) + "#");
	write("Games Won: " + std::to_string(games_won) + "#");
	write("Games Lost: " + std::to_string(games_lost) + "#");
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
	write("Enter your Bet #"); 
	write("(1):  1  (2):  10  (3):  25  (4):  50  (5): 100");

	std::string bet_string = "";
	bet_string = read();

	switch(bet_string[0])
	{
		default:
			get_bet();
			break;
		case('1'):
			bet_amount = 1;
			break;
		case('2'):
			bet_amount = 10;

			break;
		case('3'):
			bet_amount = 25;

			break;
		case('4'):
			bet_amount = 50;
			break;
		case('5'):
			bet_amount = 100;
			break;
	}
	if(bet_amount > balance)
	{
		write("You do not have enough to make that bet#");
		get_bet();
	}
	else
	{
		balance -= bet_amount;
	}

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
	}
	catch (std::exception& e) 
	{

		std::cout << "Error in player write " << e.what() <<" trying to write "<<data << std::endl;
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
}