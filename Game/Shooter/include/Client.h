#pragma once

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "..\include\Peer.h"

class StateManager;
class Bullet;

class Client
{
public:

	Client();
	~Client();

	//update function for the lobby state
	bool Update();
	//update function for the game state
	bool Update(sf::Vector2f position_);
	void Init(StateManager* stateManager_);

	bool getReady();
	void toggleReady();

	void sendBulletInfo(sf::Vector2f start_pos_, sf::Vector2f velocity_, float rotation_angle_);

	int getID();

	std::vector<Bullet*> getBullets();
	void clearBullets();

	std::map<int, Peer*> getPeers();

private:
	enum MessageType { NEW_CONNECTION, PLAYER_UPDATE, PLAYER_DISCONNECT, LOBBY_UPDATE, GAME_STARTING, NEW_CONNECT_REJECT, ADD_PEER, NEW_BULLET };
	
	int client_ID;
	sf::Vector2f position;
	bool ready;

	bool change_to_level;
	bool lobby_mode;

	int num_peers;
	std::map<int, Peer*> peers;
	std::vector<Bullet*> bullets;

	// Local network info
	sf::UdpSocket local_sock;
	sf::IpAddress local_addr;
	unsigned short local_port;

	sf::Clock clock;
	float tick;
	float dt;
	sf::Time start_time;

	// Server network info
	sf::IpAddress server_addr;
	unsigned short server_port;

	void JoinServer(sf::UdpSocket* sock_, sf::IpAddress addr_, unsigned short port_);
	void ReceiveMessage();
	void SendUpdate();

	StateManager* state_manager;
};