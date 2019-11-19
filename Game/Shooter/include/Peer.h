#pragma once
#include <SFML/Graphics.hpp>

class Peer
{
public:

	int getID();
	void setID(int ID_);

	bool getReady();
	void setReady(bool ready_);

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f position_);

private:

	int ID;
	bool ready;
	sf::Vector2f position;
};