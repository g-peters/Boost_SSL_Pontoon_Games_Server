#pragma once
#include "Player.h"
class dealer : public player
{
public:
	void write(std::string);
	void get_bet();
	std::string show_hand();
	std::string read();
	dealer(std::string);
	dealer() {}
};

