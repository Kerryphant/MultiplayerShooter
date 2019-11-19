#pragma once
#include <map>

#include "PlayerConnection.h"

// The IP address for the server
#define SERVERIP "127.0.0.1"

// The UDP port number for the server
#define SERVERPORT 4444

class Server 
{
public:

	Server();
	~Server();

	void update(sf::RenderWindow* window_);

	void receiveMessage();
	void sendClientUpdates(float dt_);

private:
	//network thing
	sf::UdpSocket socket;

	//Clock for timing the 'dt' value
	sf::Clock clock;
	float tick;
	sf::Time start_time;

	//enum for message types
	enum MessageType { NEW_CONNECTION, PLAYER_UPDATE, PLAYER_DISCONNECT, LOBBY_UPDATE, GAME_STARTING, NEW_CONNECT_REJECT, ADD_PEER };

	//container for all players
	std::map<int, PlayerConnection*> connected_players;
	
	//member variables
	int num_connected_players = 0;
	bool lobby_mode = true;
};