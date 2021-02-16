#include "Player.h"



void player::player_show_cards()
{
	std::string card_hand;
	for (int i = 0; i < player_cards.size(); ++i) {
		card_hand = player_cards[i].get_face();
		card_hand += player_cards[i].get_suit();
		//std::cout << "\n";
	}
	write("Here are your cards");
}

void player::card_back_to_deck(card*)
{
}

void player::take_card(std::shared_ptr<deck> deck)
{
	player_cards.push_back(deck->get_card());
	std::cout << player_name << " took card\n";
	player_cards.back().get_face();
	player_cards.back().get_suit();
	std::cout << "\n";


}

player::player(std::string name)
{
	player_name = name; // dealer
}

void player::get_name()
{

	//boost::asio::write(*sock, boost::asio::buffer("Enter your name\n"));
	write("Enter your name.\n");
	player_name = read();
}

player::player(ssl_sock_ptr& s) : sock(std::move(s))
{

	std::cout << "Player connected to server: " << player_name << std::endl;
}





bool player::get_ready()
{
	return ready;
}

std::string player::read()
{
	boost::asio::read_until(*sock, buffer, "\n");
	std::string data = boost::asio::buffer_cast<const char*>(buffer.data());
	std::cout << data << std::endl;
	buffer.consume(data.size());
	return data;
}



void player::write(std::string data)
{
	boost::asio::write(*sock, boost::asio::buffer(data));

}

std::string player::get_input()
{
	std::string data;
	std::getline(std::cin, data);
	return data;
}


player::~player(){
	if (t != nullptr)
	{
		t->join();
		delete t;
	}
}