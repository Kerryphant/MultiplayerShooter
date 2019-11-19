#pragma once
#include "..\include\IState.h"

#include <SFML/Graphics.hpp>

#include "..\include\Cursor.h"

class Button;

class MenuState : public IState
{
public:

	MenuState();
	~MenuState();

	void Init(sf::RenderWindow* hwnd_, Input* input_, StateManager* state_manager_);
	void CleanUp();

	bool HandleInput();
	bool Update(float frame_time_);
	void Render();

private:
	sf::Texture background_texture;
	sf::RectangleShape background_shape;
	sf::View menu_view;

	Cursor cursor;
	Button* buttons[4];
};