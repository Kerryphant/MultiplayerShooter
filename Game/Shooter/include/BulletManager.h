#pragma once
#include "..\include\Bullet.h"

class Client;

class BulletManager
{
public:

	BulletManager();
	~BulletManager();

	void createNewBullet(sf::Vector2f cursor_pos, sf::Vector2f player_pos, Client* client_);
	void updateBullets(float dt_, Client* client_);

	std::vector<Bullet*> getBullets();
	void renderBullets(sf::RenderWindow* hwnd_);

private:

	std::vector<Bullet*> bullets;

};