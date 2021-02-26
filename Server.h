#include <vector>
#include <map>
#include <memory>
#include "Card.h"
#include "Deck.h"
#include <deque>
#include "Game.h"
#include "Player.h"
#include "Lobby.h"
#include <utility> 
#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/asio/ssl.hpp>
typedef boost::asio::ip::tcp::socket bsock;
typedef std::unique_ptr<bsock> sock_ptr;
typedef boost::asio::ssl::stream <bsock> ssl_socket;
typedef std::unique_ptr<ssl_socket> ssl_sock_ptr;
using boost::asio::ip::tcp;

class server {

public:
	server(boost::asio::io_context&, int);
private:
	void init_ssl();
	boost::asio::io_context& context;
	tcp::endpoint end;
	tcp::acceptor acceptor;;
	boost::asio::ssl::context ssl_context;
	std::vector<boost::shared_ptr<player>> vec_players;

	lobby main_lobby;
	void accept();
};