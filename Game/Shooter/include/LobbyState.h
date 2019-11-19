#pragma once
#include "..\include\IState.h"

#include "..\include\Cursor.h"
#include "..\include\Peer.h"

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

class Button;

class LobbyState : public IState
{
public:

	LobbyState();
	~LobbyState();

	void Init(sf::RenderWindow* hwnd_, Input* input_, StateManager* state_manager_);
	void CleanUp();

	bool HandleInput();
	bool Update(float frame_time_);
	void Render();


	enum MessageType { NEW_CONNECTION, PLAYER_UPDATE, PLAYER_DISCONNECT, LOBBY_UPDATE, GAME_STARTING, NEW_CONNECT_REJECT, ADD_PEER};

private:

	sf::Texture background_texture;
	sf::Texture ready_texture;
	sf::Texture unready_texture;
	sf::RectangleShape background_shape;
	sf::RectangleShape ready_shape;
	sf::View multiplayer_view;
	
	Cursor cursor;

	bool ready;
	Button* ready_button;
	std::vector<sf::RectangleShape*> ready_sprites;
	int client_ID;

	int num_peers;
	std::map<int, Peer*> peers;

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

	void joinServer(sf::UdpSocket* sock_, sf::IpAddress addr_, unsigned short port_);
	void receiveMessage();
	void sendUpdate();
};
