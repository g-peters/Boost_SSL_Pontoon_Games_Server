#include <iostream>
#include <boost/asio/ssl.hpp>
#include <boost/asio.hpp>

typedef boost::asio::ip::tcp::socket bsock;
typedef boost::asio::ssl::stream<bsock> ssl_socket;
void write(ssl_socket&);
void read(ssl_socket&);

int main(int argc, char* argv[])
{
	if(argc !=2)
	{
		std::cout << "Error, no port number provided!\n";
		return 1;
	}
	// io context
	boost::asio::io_context io_context;
	// ssl context
	boost::asio::ssl::context ssl_context(boost::asio::ssl::context::tls);
	// ssl socket
	ssl_socket sock(io_context,ssl_context);
	boost::asio::ip::tcp::resolver resolv(io_context);
	ssl_context.load_verify_file("server.crt");
	auto endpoints = resolv.resolve("127.0.0.1", argv[1]);
	boost::asio::connect(sock.next_layer(), endpoints);
	sock.handshake(boost::asio::ssl::stream_base::client);
	// read from sock
	read(sock);


	return 0;
}
void write(ssl_socket& sock){
	std::string data;
	std::cout << ">\n";
	std::getline(std::cin, data);
	boost::asio::write(sock, boost::asio::buffer(data + "#"));

	read(sock);
}


void read(ssl_socket& sock){

	boost::asio::streambuf buf;
	boost::asio::read_until(sock, buf, "#");
	std::string data = boost::asio::buffer_cast<const char*>(buf.data());
	std::cout << data << std::endl;

	// creates loop for read/write
	write(sock);

}