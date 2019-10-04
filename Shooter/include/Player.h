#pragma once

#include <SFML/Graphics.hpp>

#include "..\include\Sprite.h"
#include "..\include\Animation.h"

class Player : public Sprite
{
public:

	Player(Input* input_);
	~Player();

	void update(float frame_time_);
	void handleInput(float frame_time_, sf::RenderWindow* window_);
	void takeDamage(int amount_);

private:

	int health;
	float move_speed;
	bool flipped;

	sf::View player_camera;
	Animation walk;
	Animation stand;
	Animation* current_animation;
};