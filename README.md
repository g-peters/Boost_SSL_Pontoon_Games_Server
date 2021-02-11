Compilation

g++ -pthread *.cpp -o server -lcrypto -lssl

v.0.1 

Requires 3 clients to connect to test handling of multiple connections

upon each client connection, server will perform ssl handshake, upon successful handshake, read will be called
to get client name, on third player connection (4 players inc server/dealer)
the game will start.

Game is limited to dealing 2 cards to each player from top of the randomly shuffled deck.