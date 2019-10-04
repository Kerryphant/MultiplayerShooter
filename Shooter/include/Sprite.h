#pragma once

#include <SFML/Graphics.hpp>

#include "Input.h"

class Sprite : public sf::RectangleShape
{
public:
	Sprite();
	~Sprite();

	virtual void update(float frame_time_);

	//sprite speed and directions
	void setVelocity(sf::Vector2f vel_);
	void setVelocity(float vx_, float vy_);
	sf::Vector2f getVelocity();

	//sprite state
	bool isAlive() { return alive; }
	void setAlive(bool b_) { alive = b_; }

	
	//??
	/*
	bool isCollider() { return collider; };
	void setCollider(bool b_) { collider = b_; };
	*/

	//Collision functions
	//returns the box collider for this sprite
	sf::FloatRect getCollisionBox() { return collisionBox; };
	
	//Set box colliders
	void setCollisionBox(float x_, float y_, float width_, float height_) { collisionBox = sf::FloatRect(x_, y_, width_, height_); };
	void setCollisionBox(sf::FloatRect fr_) { collisionBox = fr_; };
	
	//Implimented by subclasses
	virtual void updateCollisionBox();
	
	
	//input component
	void setInput(Input* in_) { input = in_; };

	

protected:
	//Sprite properties
	sf::Vector2f velocity;
	bool alive; //tracks if the sprite is alive and active on the screen. Used to decide on rendering ect
	sf::FloatRect collisionBox; //box collider
	sf::Texture texture; //Texture
	
	//input component
	Input* input;

};