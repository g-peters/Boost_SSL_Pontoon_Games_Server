#include <iostream>
#include <boost/asio.hpp>
#include "Server.h"


int main(int argc, char* argv[])
{
	// need to add port
	boost::asio::io_context io_context;
	server serv(io_context, 7777);
		
	return 0;
}











