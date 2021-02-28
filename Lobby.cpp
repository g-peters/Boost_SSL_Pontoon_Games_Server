#include "Lobby.h"

lobby::lobby() : num_of_multiplayers(0)
{

}
void lobby::insert_player(player_ptr p)
{
	std::cout << "player joined lobby\n";
	p->get_name();
	p->write("(S)ingle player or (M)ultiplayer?\n"); // 
	std::string input = p->read();
	// if statement here
	switch (input[0])
	{
	default: insert_player(p);
		break;
	case ('S'):
		singleplayer(p);
		break;
	case ('s'):
		singleplayer(p);
		break;
	case ('M'):
		multiplayer(p);
		// multi when implemented
		break;
	case ('m'):
		multiplayer(p);
		// multi when implemented
		break;
	}

}
void lobby::choose_single_or_multiplayer(player_ptr p)
{

}

void lobby::remove_player(player_ptr p)
{
	p->leave();
	//vec_players.erase(p);
}

void lobby::singleplayer(player_ptr p)
{
	game game;
	//game.create_dealer(); // not needed? done in CTOR
	// move player to game
	game.add_player(p);
	game.start_new_game();
}
void lobby::multiplayer(player_ptr p)
{
	vec_players.push_back(p);
	multiplayer_game.add_player(p);
	std::cout << "Number of players in vec " << vec_players.size() << std::endl;
	if(multiplayer_game.num_of_players() > 1)
	{
		for(int i = 0; i <vec_players.size(); ++i)
		{
			vec_players[i]->write("There are " + 
							std::to_string(vec_players.size() + 1) + 
							" players on the server, ready to start? (Y)es or (N)o");

			std::string input = vec_players[i]->read();
			if(input[0] == 'y' || input[0] == 'Y')
			{
				all_ready.push_back(true);
			}
			else
			{
				// remove player?
				all_ready.push_back(false);
			}
		}
		// checks if all players are ready
		if(std::find(begin(all_ready),end(all_ready), false) == end(all_ready))
		{
			multiplayer_game.start_new_game();
		}
		else
		{

		}
	}
}