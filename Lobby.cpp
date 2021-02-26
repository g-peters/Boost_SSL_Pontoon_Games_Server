#include "Lobby.h"

void lobby::insert_player(player_ptr p)
{
	std::cout << "player joined lobby\n";
	p->get_name();
	p->write("(S)ingle player or (M)ultiplayer?\n"); // 
	std::string input = p->read();
	// if statement here
	std::cout << "player chose " << input;
	// create game
	singleplayer(p);
}


void lobby::remove_player(player_ptr p)
{

}

void lobby::singleplayer(player_ptr p)
{
	game game;
	game.create_dealer();
	// move player to game
	game.add_player(p);
	game.start_new_game();
}
