#include "Server.h"

server::server(boost::asio::io_context& ctx, int port)
								: context(ctx),
								end(tcp::v4(), port), acceptor(ctx, end), 
								ssl_context(boost::asio::ssl::context::tls)
{
	// initialise ssl then listen for connections
	init_ssl();
	accept();
}

void server::init_ssl()
{
	// code adapted from (boost, n.d.-a)
	ssl_context.use_certificate_chain_file("server.crt");
	ssl_context.use_private_key_file("server.key", boost::asio::ssl::context::pem);
	ssl_context.use_tmp_dh_file("dh512.pem");
}

void server::accept()
{
		// code adapted from (boost, n.d.-a)
		std::cout << "Listening for connections\n";

		ssl_sock_ptr sock(new ssl_socket(context, ssl_context));
		acceptor.accept(sock->next_layer());
		sock->handshake(boost::asio::ssl::stream_base::server);
		boost::shared_ptr<player> new_player(new player(sock));
		std::thread t(&lobby::insert_player, &main_lobby, new_player);
	
		accept();
}

