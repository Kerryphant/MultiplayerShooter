#pragma once
#include <SFML/Graphics.hpp>
#include "..\include\Animation.h"
#include "..\include\Sprite.h"

class Peer
{
public:

	Peer();
	~Peer();

	int getID();
	void setID(int ID_);

	bool getReady();
	void setReady(bool ready_);

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f position_);

	void setUpTexture();
	void updateSprite(float frame_time_);
	Sprite getShape();

private:

	int ID;
	bool ready;
	sf::Vector2f position;

	bool flipped;
	sf::Texture texture;
	Sprite sprite;

	Animation* current_animation;
	Animation walk;
	Animation stand;
};