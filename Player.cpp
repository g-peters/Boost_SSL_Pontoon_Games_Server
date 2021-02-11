#include "Player.h"



void player::player_show_cards()
{
	for (int i = 0; i < player_cards.size(); ++i) {
		std::cout << player_name << "\n got card ";
		player_cards[i].get_face();
		player_cards[i].get_suit();
		std::cout << "\n";
	}
}

void player::card_back_to_deck(card*)
{
}

void player::take_card(deck* player_hand)
{
	player_cards.push_back(player_hand->get_card());
	std::cout << player_name << " took card\n";
	player_cards.back().get_face();
	player_cards.back().get_suit();
	std::cout << "\n";


}

player::player(std::string name, std::deque<card*> deck_of_card, deck* dec_class)
{
	player_name = name; // dealer
}

void player::get_name()
{ 
	boost::asio::write(*sock, boost::asio::buffer("Enter your name#"));
	read();
}

player::player(std::deque<card*> card, deck* deck, ssl_sock_ptr& s) : sock(std::move(s))
{
	// on player connect, player is created, calls get name
	get_name();
	std::cout << "Player connected to server: " << player_name << std::endl;
}

void player::read() {
	boost::system::error_code ec;
	boost::asio::streambuf buf;
	boost::asio::read_until(*sock, buf, "#");
	std::string data = boost::asio::buffer_cast<const char*>(buf.data());
	std::cout << data << std::endl;
	// temporary for testing 
	player_name = data;
	//write(sock);

}