#include <iostream>
#include <boost/asio.hpp>
#include "Game.h"
#include "Server.h"


int main(int argc, char* argv[])
{
	
	if(argc < 2)
	{
		std::cout << "Error, No port Provided!\n";
		return 1;
	}
	
	boost::asio::io_context io_context;
	// create server object, passes io_context and port for server to listen on
	server serv(io_context, std::atoi(argv[1]));

		
	return 0;
}











