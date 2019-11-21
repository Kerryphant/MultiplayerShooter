#pragma once
#include "..\include\IState.h"

#include "..\include\Cursor.h"
#include "..\include\Client.h"
#include <SFML/Graphics.hpp>

class Button;

class LobbyState : public IState
{
public:

	LobbyState();
	~LobbyState();

	void Init(sf::RenderWindow* hwnd_, Input* input_, StateManager* state_manager_);
	void CleanUp();

	bool HandleInput();
	bool Update(unsigned int w_, unsigned int h_, float frame_time_);
	void Render();

private:

	sf::Texture background_texture;
	sf::Texture ready_texture;
	sf::Texture unready_texture;
	sf::RectangleShape background_shape;
	sf::RectangleShape ready_shape;
	sf::View multiplayer_view;
	
	Cursor cursor;
	Client* client;

	Button* ready_button;
};
