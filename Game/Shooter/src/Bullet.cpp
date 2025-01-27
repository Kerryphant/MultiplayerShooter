#include "..\include\Bullet.h"

Bullet::Bullet()
{
	alive = false;

	//texture prep
	blue.loadFromFile("Media/Sprites/Bullets/BlueBullet.png");
	red.loadFromFile("Media/Sprites/Bullets/RedBullet.png");

	changeTexture(BLUE);
	current_tex = BLUE;

	speed = 300.f;

	setSize(sf::Vector2f(7.5, 12));

	setCollisionBox(this->getPosition().x, this->getPosition().y, 5, 8);

	updateCounter = 0;

}

Bullet::~Bullet()
{

}


void Bullet::update(float dt_)
{
	if (alive)
	{
		changeTexture(current_tex);

		move(velocity*dt_);

		updateCollisionBox();
	}
}

void Bullet::changeTexture(BulletTexture tex_)
{
	//change texture according to passed enum
	switch (tex_)
	{
	case BLUE:
		this->setTexture(&blue);
		break;
	case RED:
		this->setTexture(&red);
		break;
	default:
		break;
	}
}

void Bullet::setIsEnemy(bool enemy)
{
	if (enemy)
	{
		current_tex = RED;
	}
	else
	{
		current_tex = BLUE;
	}
}

bool Bullet::getIsEnemy()
{
	if (current_tex == RED)
	{
		return true;
	}
	
	return false;
}
