#pragma once
#include "..\include\Sprite.h"
#include <functional>
#include <iostream>

class Bullet : public Sprite
{

public:

	Bullet();
	~Bullet();

	//used to change textures
	enum BulletTexture { BLUE, RED };

	void update(float dt_);
	void setSpeed(float speed_) { speed = speed_; };
	void changeTexture(BulletTexture tex_);
	float getUpdateCounter() { return updateCounter; }
	void setUpdateCounter(float value_) { updateCounter = value_; }
	
	
	void setIsEnemy(bool enemy);
	bool getIsEnemy();

private:

	BulletTexture current_tex;

	sf::Texture blue;
	sf::Texture red;
	float speed;
	
	float updateCounter;
	//bullet's behaviour called every update
	std::function<bool(Bullet* thisBullet_) > bulletAIFunction;

};