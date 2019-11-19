#include "PlayerConnection.h"

PlayerConnection::PlayerConnection() : health(100), last_message_time(0), player_id(0), port(0), received_this_frame(false)
{
}

PlayerConnection::~PlayerConnection()
{
}

float PlayerConnection::getLastMessageTime()
{
	return last_message_time;
}

bool PlayerConnection::getRecievedThisFrame()
{
	return received_this_frame;
}

void PlayerConnection::setRecievedThisFrame(bool toggle_)
{
	received_this_frame = toggle_;
}

void PlayerConnection::predictNewPosition()
{
}

sf::IpAddress PlayerConnection::getAddress()
{
	return address;
}

void PlayerConnection::setAddress(sf::IpAddress address_)
{
	address = address_;
}

unsigned short PlayerConnection::getPort()
{
	return port;
}

void PlayerConnection::setPort(unsigned short port_)
{
	port = port_;
}

int PlayerConnection::getID()
{
	return player_id;
}

void PlayerConnection::setID(int ID_)
{
	player_id = ID_;
}

bool PlayerConnection::getReady()
{
	return ready;
}

void PlayerConnection::setReady(bool ready_)
{
	ready = ready_;
}

sf::Vector2f PlayerConnection::getPosition()
{
	return position;
}

void PlayerConnection::setPosition(sf::Vector2f position_)
{
	position = position_;
}
