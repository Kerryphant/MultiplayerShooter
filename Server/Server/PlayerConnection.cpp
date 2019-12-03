#include "PlayerConnection.h"

PlayerConnection::PlayerConnection() : health(100), last_message_time(0), player_id(0), port(0), received_this_frame(false), game_time(0)
{
}

PlayerConnection::~PlayerConnection()
{
}

float PlayerConnection::getLastMessageTime()
{
	return last_message_time;
}

void PlayerConnection::incrementLastMessageTime(float amount_)
{
	last_message_time += amount_;
}

bool PlayerConnection::getRecievedThisFrame()
{
	return received_this_frame;
}

void PlayerConnection::setRecievedThisFrame(bool toggle_)
{
	received_this_frame = toggle_;
	if (received_this_frame)
	{
		last_message_time = 0;
	}
	
}

void PlayerConnection::predictNewPosition()
{
	float predictedX = -1.0f;
	float predictedY = -1.0f;

	//const int msize = m_Messages.size();
	//if (msize < 3) {
	//	return sf::Vector2f(predictedX, predictedX);
	//}
	//const TankMessage& msg0 = m_Messages[msize - 1];
	//const TankMessage& msg1 = m_Messages[msize - 2];
	//const TankMessage& msg2 = m_Messages[msize - 3];

	// FIXME: Implement prediction here!
	// You have:
	// - the history of position messages received, in "m_Messages"
	//   (msg0 is the most recent, msg1 the 2nd most recent, msg2 the 3rd most recent)
	// - the current time, in "gameTime"
	//
	// You need to update:
	// - the predicted position at the current time, in "predictedX" and "predictedY"

	//v = change in pos / change in time
	//float xVel = (msg1.x - msg0.x) / (msg1.time - msg0.time);
	//float yVel = (msg1.y - msg0.y) / (msg1.time - msg0.time);

	//predictedX = msg0.x + xVel;
	//predictedY = msg0.y + yVel;


	//return sf::Vector2f(predictedX, predictedY);
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

float PlayerConnection::getGameTime()
{
	return game_time;
}

void PlayerConnection::setGameTime(float time_)
{
	game_time = time_;
}
