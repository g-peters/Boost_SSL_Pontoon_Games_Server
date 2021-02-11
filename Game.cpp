#include "Game.h"
#include "Player.h"


game::game(boost::asio::io_context& context, int p) : port(p)
{
	deck_cards = deck_.deck_of_cards();
	game_started = false;
	setup_players();
	listen();
	std::cout << "game created\n";

}


void game::setup_players()
{
	vec_players.push_back(player("Dealer", deck_cards, ptr_deck));
}

void game::listen()
{	
	std::cout << "Listening\n";

	try
	{
		tcp::endpoint end(tcp::v4(), port);
		boost::asio::io_context io_context;
		// ssl context
		boost::asio::ssl::context ssl_context(boost::asio::ssl::context::tls);
		// setup ssl 
		ssl_context.use_certificate_chain_file("server.crt");
		ssl_context.use_private_key_file("server.key", boost::asio::ssl::context::pem);
		ssl_context.use_tmp_dh_file("dh512.pem");
		std::cout << "SSL setup\n";
		
		while (!game_started)
		{
			
			
			tcp::acceptor accept(io_context, end);
			// create new sock per connection
			ssl_sock_ptr sock(new ssl_socket (io_context, ssl_context));
			accept.accept(sock->next_layer());
			std::cout << "Accepted Connection\n";
			// ssl handshake
			sock->handshake(boost::asio::ssl::stream_base::server);
			std::cout << "Connection Complete\n";
			// creates new player object for each connection
			vec_players.push_back(player(deck_cards, ptr_deck, sock));
			// temporary to test server handling multiple connections
			if (vec_players.size() == 4)
			{
				game_started = true;
				start_game();
			}
			
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception Listening for connections: " << e.what() << "\n";
	}

}

void game::start_game()
{
	// deals each player 2 cards
	for (int i = 0; i < 2; ++i)
	{
		// number of players
		for (int j = 0; j < vec_players.size(); ++j)
		{
			vec_players[j].take_card(ptr_deck);
		}

	}
	// testing
	for (int x = 0; x < vec_players.size(); ++x)
	{
		vec_players[x].player_show_cards();
	}
	// reset server to listen ready for new game
	game_started = false;
	listen();
}

