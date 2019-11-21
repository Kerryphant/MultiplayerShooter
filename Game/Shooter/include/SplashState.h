#pragma once
#include "..\include\IState.h"

#include <SFML/Graphics.hpp>

class SplashState : public IState
{
public:

	SplashState();
	~SplashState();

	void Init(sf::RenderWindow* hwnd_, Input* input_, StateManager* state_manager_);
	void CleanUp();

	bool HandleInput();
	bool Update(unsigned int w_, unsigned int h_, float frame_time_);
	void Render();

private:

	sf::Texture background_texture;
	sf::RectangleShape background_shape;
	sf::View splash_view;
};