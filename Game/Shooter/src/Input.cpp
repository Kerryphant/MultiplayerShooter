#include "../include/Input.h"
#include "../include/SFML/Graphics.hpp"



void Input::setKeyDown(int key_)
{
	if (key_ >= 0)
	{
		keys[key_] = true;
	}
}
void Input::setKeyUp(int key_)
{
	if (key_ >= 0)
	{
		keys[key_] = false;
	}
}
bool Input::isKeyDown(int key_)
{
	return keys[key_];
}
void Input::setMouseX(int lx_)
{
	mouse.x = lx_;
}
void Input::setMouseY(int ly_)
{
	mouse.y = ly_;
}
void Input::setMousePosition(int lx_, int ly_)
{
	setMouseX(lx_);
	setMouseY(ly_);
}
int Input::getMouseX()
{
	return mouse.x;
}
int Input::getMouseY()
{
	return mouse.y;
}
void Input::setMouseLeftDown(bool down_)
{
	mouse.left = down_;
}
bool Input::isMouseLeftDown()
{
	return mouse.left;
}

