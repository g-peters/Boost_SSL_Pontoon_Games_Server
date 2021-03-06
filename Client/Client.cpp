#include <iostream>
#include <boost/asio/ssl.hpp>
#include <boost/asio.hpp>

typedef boost::asio::ip::tcp::socket bsock;
typedef boost::asio::ssl::stream<bsock> ssl_socket;
void write(ssl_socket&);
void read(ssl_socket&);
const char  no_response('#');

int main(int argc, char* argv[])
{
	// io context
	boost::asio::io_context io_context;
	// ssl context
	boost::asio::ssl::context ssl_context(boost::asio::ssl::context::tls);
	// ssl socket
	ssl_socket sock(io_context, ssl_context);
	boost::asio::ip::tcp::resolver resolv(io_context);
	ssl_context.load_verify_file("server.crt");
	auto endpoints = resolv.resolve("127.0.0.1", argv[1]);
	boost::asio::connect(sock.next_layer(), endpoints);
	sock.handshake(boost::asio::ssl::stream_base::client);
	// read from sock

	try 
	{
		read(sock);
	}
	catch (std::exception& e) 
	{ 
		std::cout << "\nError attempting to read: " << e.what(); 
	}

	return 0;
}
void write(ssl_socket& sock) {
	std::string data = "";
	std::cout << ">\n";
	std::getline(std::cin, data);
	boost::asio::write(sock, boost::asio::buffer(data + "\n"));

	read(sock);
}


void read(ssl_socket& sock)
{
	boost::asio::streambuf buf;
	boost::asio::read_until(sock, buf, "\n");
	std::istream is(&buf);
	std::string data = "";
	std::getline(is, data);
	if (data == "exit_game") 
	{
		try 
		{
			sock.shutdown();
		}
		catch (std::exception& e) {}
		//Receives EOF error which is expected with SSL socket shutdown
		// https://stackoverflow.com/questions/25587403/boost-asio-ssl-async-shutdown-always-finishes-with-an-error ( Tanner Sansbury )
		//std::cout << "Error in shutdown " << e.what();
		return;
	}
	if (data.back() == no_response) 
	{
		data.pop_back();
		std::cout << data << std::endl;
		read(sock);
	}
	else
	{
		std::cout << data << std::endl;
		try
		{
			write(sock);
		}
		catch (std::exception& e)
		{
			std::cout << "\nError attempting to write: " << e.what();
		}
	}
}
