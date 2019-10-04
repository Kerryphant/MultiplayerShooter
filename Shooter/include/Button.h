#pragma once
#include "..\include\Sprite.h"
#include <functional>
#include <string>

class Button : public Sprite
{

public:

	Button(float x_pos_, float y_pos_);
	~Button();

	//set what action the button should take on click
	void setAction(std::function<void()> func_) { execute = func_; }
	
	//set sprite
	void setSprite(std::string spritePath_);

	//check if button contains the coords passed
	void checkClick(float x_, float y_);

private:
	
	//Button performs it's action
	std::function<void() > execute;

};