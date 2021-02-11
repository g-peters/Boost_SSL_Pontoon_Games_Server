#pragma once
#include <iostream>
#include <map>


class card
{
private:
	int value;
	char suit;
	int face;
	void assign_value();
	std::map<int, std::string> card_face;
	std::map<char, std::string> suits;

	void fill_map_face();
	void fill_map_suit();

public:
	card(int f, int s) :suit(s), face(f) {
		assign_value(); // constructor
		fill_map_face();
		fill_map_suit();
	}
	card(const card&); // copy constructor
	card(const card&&); // move constructor
	char get_suit();
	int get_face();
	int get_value();
};

