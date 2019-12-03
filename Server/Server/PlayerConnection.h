#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

class PlayerConnection
{
public:

	PlayerConnection();
	~PlayerConnection();

	float getLastMessageTime();
	void incrementLastMessageTime(float amount_);

	bool getRecievedThisFrame();
	void setRecievedThisFrame(bool toggle_);

	void predictNewPosition();

	sf::IpAddress getAddress();
	void setAddress(sf::IpAddress address_);
	
	unsigned short getPort();
	void setPort(unsigned short port_);
	
	int getID();
	void setID(int ID_);

	bool getReady();
	void setReady(bool ready_);

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f position_);

	float getGameTime();
	void setGameTime(float time_);

private:

	int player_id;
	int health;
	sf::Vector2f position;
	bool ready;
	float game_time;

	float last_message_time;
	bool received_this_frame;

	sf::IpAddress address;
	unsigned short port;
};