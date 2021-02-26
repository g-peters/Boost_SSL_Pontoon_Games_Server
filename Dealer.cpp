#include "Dealer.h"

void dealer::write(std::string data)
{
	//std::cout <<"Dealer: " << data << std::endl;
}

void dealer::get_bet()
{
	// dealer do nothing, 
}

std::string dealer::show_hand()
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
	card_hand += +" (" + std::to_string(value) + ")";
	return card_hand;
}

dealer::dealer(std::string name) : player(name)
{

}
std::string dealer::read() {
	return "";
	// DO NOTHING
}