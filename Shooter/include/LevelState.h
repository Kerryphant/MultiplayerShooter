#pragma once
#include "..\include\IState.h"

#include <SFML/Graphics.hpp>

class LevelState : public IState
{
public:

	LevelState();
	~LevelState();

	void Init(sf::RenderWindow* hwnd_, Input* input_, StateManager* state_manager_);
	void CleanUp();

	bool HandleInput();
	bool Update(float frame_time);
	void Render();

private:
	sf::View level_view;
};