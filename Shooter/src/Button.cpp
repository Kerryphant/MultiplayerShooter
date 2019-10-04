#include "..\include\Button.h"

Button::Button(float x_pos_, float y_pos_)
{
	this->setPosition(x_pos_, y_pos_);
	setSize(sf::Vector2f(400, 100));

	setCollisionBox(this->getPosition().x, this->getPosition().y, 400, 100);
}

Button::~Button()
{

}

void Button::setSprite(std::string spritePath_)
{
	//load desired sprite
	texture.loadFromFile(spritePath_);
	setTexture(&texture);
}

void Button::checkClick(float x_, float y_)
{
	//if the click is within the button
	if (x_ >= this->getPosition().x && x_ <= this->getPosition().x + 400 && y_ >= this->getPosition().y && y_ <= this->getPosition().y + 100) {
		//execute the behaviour passed in lambda
		execute();
	}
}

