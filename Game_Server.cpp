#include <iostream>
#include <boost/asio.hpp>
#include "Game.h"


int main(int argc, char* argv[])
{
	if(argc !=2)
	{
		std::cout << "Error, no port number provided!\n";
		return 1;

	}


	boost::asio::io_context io_context;
	game game(io_context, std::atoi(argv[1]));
		
	return 0;
}











