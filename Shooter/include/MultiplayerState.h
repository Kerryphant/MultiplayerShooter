#pragma once
#include "..\include\IState.h"

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

class MultiplayerState : public IState
{
public:

	MultiplayerState();
	~MultiplayerState();

	void Init(sf::RenderWindow* hwnd_, Input* input_, StateManager* state_manager_);
	void CleanUp();

	bool HandleInput();
	bool Update(float frame_time_);
	void Render();

private:

	sf::Texture background_texture;
	sf::RectangleShape background_shape;
	sf::View multiplayer_view;

	sf::TcpSocket socket;
};
