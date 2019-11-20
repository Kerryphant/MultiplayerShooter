#include "..\include\Sprite.h"

Sprite::Sprite() : RectangleShape(), alive(true) {}

Sprite::~Sprite() {}

//override this function to provide functionality
void Sprite::update(float frame_time_)
{
}

//Sets the velocity of the sprite
void Sprite::setVelocity(sf::Vector2f vel_)
{
	velocity = vel_;
}

void Sprite::setVelocity(float vx_, float vy_)
{
	velocity.x = vx_;
	velocity.y = vy_;
}

//get sprite velocity
sf::Vector2f Sprite::getVelocity()
{
	return velocity;
}

//default function for collision update
void Sprite::updateCollisionBox()
{
	//Axis Aligned Bounding Box, based on Sprite size and position.
	//Shape could be smaller/larger and offset if required.
	//Can be overwritten by child classes
	collisionBox.left = getPosition().x;
	collisionBox.top = getPosition().y;
}

void Sprite::createTexture(std::string path_)
{
	texture.loadFromFile(path_);

	setTexture(&texture);
}
