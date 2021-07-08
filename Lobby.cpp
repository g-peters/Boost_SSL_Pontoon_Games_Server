#include "Lobby.h"

lobby::lobby()
{
	multi_game = nullptr;
	multiplayer_size = 0;
}

lobby::~lobby()
{
	delete multi_game;
}



void lobby::insert_player(player_ptr p)
{
	std::cout << "player joined lobby\n";
	// code adapted from (cppreference, 2021e)
	std::thread t(&lobby::main_menu,this,std::move(p));
	t.detach();	
}

void lobby::main_menu(player_ptr p)
{	
	std::string input = "";
	do
	{
		p->write("1: New Game#");
		p->write("2: Show Balance#");
		p->write("3: Show stats#");
		p->write("4: Exit");
		input = p->read();
		
		switch (input[0])
		{
		case('1'):
			single_or_multi(p);
			break;
		case('2'):
			p->write("Balance : " + std::to_string(p->get_balance()) + "#");
			game::sleep(1);
			main_menu(p);
			break;
		case ('3'):
			p->print_stats();
			game::sleep(1);
			main_menu(p);
			break;
		case ('4'):
			game::sleep(1);
			p->save_data();
			p->leave();
			break;
		}
	}
	while(input[0] != '1' && input[0] != '2' && input[0] != '3' && input[0] != '4');
}

void lobby::single_or_multi(player_ptr p )
{

	std::string input = "";
	do
	{
		p->write("1: Single player     2: Multiplayer");
		input = p->read();
		if (input[0] == '1')
		{
			singleplayer(std::move(p));
		}
		else if (input[0] == '2')
		{	

			multiplayer_queue.emplace(p);
			std::cout << "Multiplayer size : " << multiplayer_queue.size() << std::endl;
			if (multiplayer_queue.size() == 1)
			{
				multi_game = new game();
				//multi_game->create_dealer();

				multiplayer_queue.front()->write("How many players to wait for? ( Max 5 )");
				std::string input = multiplayer_queue.front()->read();
				multiplayer_size = std::stoi(input);	

			}
			if (multiplayer_queue.size() == multiplayer_size)
			{

				for (int i = 0; i < multiplayer_size; ++i)
				{
					player_vec.push_back(std::move(multiplayer_queue.front()));
					//after moving each player to game, removes them from queue
					multiplayer_queue.pop();
				}
				multiplayer(multiplayer_size);
			}
		}
	}
	while(input[0] != '1' && input [0] != '2');
	
}



void lobby::singleplayer(player_ptr p)
{
	game game;
	game.create_dealer();
	game.add_player(std::move(p));
	game.start_new_game(this);
}
 

void lobby::multiplayer(unsigned short int sz)
{
	for (int i = 0; i < sz; ++ i)
	{
		multi_game->add_player(std::move(player_vec[i]));
	}
	if (multi_game->get_num_players()  == sz)
	{
		// passes this pointer to game so players can be returned to lobby
		multi_game->start_multiplayer_game(this);
		delete multi_game;
	}	
}