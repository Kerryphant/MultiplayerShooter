#include "..\include\Cursor.h"

Cursor::Cursor()
{
	texture.loadFromFile("Media/Sprites/Cursor.png");
	texture2.loadFromFile("Media/Sprites/Target.png");

	this->setTexture(&texture);
	this->setSize(sf::Vector2f(48, 48));

	speed = 300.f;
}

Cursor::~Cursor()
{

}

void Cursor::update(Input* input_)
{
	//set this object's position to the cursor's position
	this->setPosition((float)input_->getMouseX(), (float)input_->getMouseY());
}

void Cursor::changeTexture(CursorTexture tex_)
{
	//switch to the desired texture
	switch (tex_)
	{
	case POINTER:
		this->setTexture(&texture);
		break;
	case TARGET:
		this->setTexture(&texture2);
		break;
	default:

		break;
	}
}

