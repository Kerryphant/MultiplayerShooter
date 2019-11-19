#include "..\include\Peer.h"

int Peer::getID()
{
	return ID;
}

void Peer::setID(int ID_)
{
	ID = ID_;
}

bool Peer::getReady()
{
	return ready;
}

void Peer::setReady(bool ready_)
{
	ready = ready_;
}

sf::Vector2f Peer::getPosition()
{
	return position;
}

void Peer::setPosition(sf::Vector2f position_)
{
	position = position_;
}
