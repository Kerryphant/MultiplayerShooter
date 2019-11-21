#include "..\include\Peer.h"

Peer::Peer() : flipped(false), current_animation(nullptr), ID(-1), ready(false)
{
	sprite.setSize(sf::Vector2f(51, 64));
	sprite.setPosition(100, 100);

	//each frame is 51 wide, 64 tall
	walk.addFrame(sf::IntRect(0, 0, 51, 64));
	walk.addFrame(sf::IntRect(51, 0, 51, 64));
	walk.addFrame(sf::IntRect(102, 0, 51, 64));
	walk.addFrame(sf::IntRect(153, 0, 51, 64));
	walk.addFrame(sf::IntRect(204, 0, 51, 64));
	walk.addFrame(sf::IntRect(255, 0, 51, 64));
	walk.addFrame(sf::IntRect(306, 0, 51, 64));
	walk.addFrame(sf::IntRect(357, 0, 51, 64));

	walk.setFrameSpeed(1.f / 10.f);

	stand.addFrame(sf::IntRect(0, 66, 51, 64));
	stand.addFrame(sf::IntRect(51, 66, 51, 64));

	stand.setFrameSpeed(3.f / 10.f);

	current_animation = &stand;
}

Peer::~Peer()
{
}

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
	sprite.setPosition(position_);
}

void Peer::setUpTexture()
{
	std::string path = "Media/Sprites/Character/";
	path += std::to_string(ID);
	path += "Char.png";

	sprite.createTexture(path);
	 
	sprite.setTextureRect(current_animation->getCurrentFrame());
	sprite.setPosition(position);
}

void Peer::updateSprite(float frame_time_)
{
	current_animation->animate(frame_time_);

	sprite.setTextureRect(current_animation->getCurrentFrame());
	stand.setFlipped(flipped);
	current_animation = &stand;

	sprite.updateCollisionBox();
}

Sprite Peer::getShape()
{
	return sprite;
}
