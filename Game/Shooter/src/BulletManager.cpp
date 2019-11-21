#include "..\include\BulletManager.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include "..\include\Vector.h"
#include "..\include\Client.h"

BulletManager::BulletManager()
{
	for (int i = 0; i < 8; i++)
	{
		Bullet* temp_bullet = new Bullet();
		temp_bullet->setAlive(false);

		bullets.push_back(temp_bullet);
	}
}

BulletManager::~BulletManager()
{
}

void BulletManager::createNewBullet(sf::Vector2f cursor_pos, sf::Vector2f player_pos, Client* client_)
{
	//Bullet* target_bullet = nullptr;

	/*for (Bullet* current_bullet : bullets) 
	{
		//if we are on the last bullets and its being used
		if (current_bullet == bullets.back() && current_bullet->isAlive())
		{
			//add a new bullet to the vector
			Bullet* new_bullet = new Bullet;
			new_bullet->setAlive(true);
			
			bullets.push_back(new_bullet);

			target_bullet = new_bullet;
			break;
		}
		//else if the bullet is not being used
		else if (!(current_bullet->isAlive()))
		{
			//set the pointer
			target_bullet = current_bullet;
			target_bullet->setAlive(true);
			break;
		}
	}*/

	//get the x and y values for the vector we will make
	float vectorX = cursor_pos.x - (player_pos.x + 32);
	float vectorY = cursor_pos.y - (player_pos.y + 32);

	sf::Vector2f vel = Vector::normalise(sf::Vector2f(vectorX, vectorY));
	//Multiply so bullets all move at the same speed
	vel.x = vel.x * 400;
	vel.y = vel.y * 400;
	//target_bullet->setVelocity(vel);

	//normalise so we just have the directions
	sf::Vector2f playerPos = Vector::normalise(sf::Vector2f(player_pos.x + 25, player_pos.y + 32));

	//rotate the sprite of tempBullet to be in the direction of the cursor
	float angle = (float)(atan2(vel.x, vel.y) * (180 / M_PI));
	if (angle > 90)
	{
		angle = 450 - angle;
	}
	else
	{
		angle = 90 - angle;
	}
	angle += 90;

	/*if (target_bullet)
	{
		target_bullet->setRotation(angle);
	}*/
	
	//target_bullet->setPosition(player_pos.x + 32, player_pos.y + 32);

	client_->sendBulletInfo(sf::Vector2f(player_pos.x + 32, player_pos.y + 32), vel, angle);
}

void BulletManager::updateBullets(float dt_, Client* client_)
{
	std::vector<Bullet*> network_bullets = client_->getBullets();

	for (auto current_bullet : network_bullets)
	{
		current_bullet->setAlive(true);
		bullets.push_back(current_bullet);
	}

	client_->clearBullets();

	for (auto current_bullet : bullets)
	{
		if (current_bullet->isAlive())
		{
			current_bullet->update(dt_);
		}
		
	}
}

std::vector<Bullet*> BulletManager::getBullets()
{
	return bullets;
}

void BulletManager::renderBullets(sf::RenderWindow* hwnd_)
{
	for (auto current_bullet : bullets)
	{
		if (current_bullet->isAlive())
		{
			hwnd_->draw(*current_bullet);
		}
	}
}
