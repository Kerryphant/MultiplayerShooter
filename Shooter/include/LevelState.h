#pragma once
#include "..\include\IState.h"

#include <SFML/Graphics.hpp>

#include "..\include\Player.h"
#include "..\include\TileMap.h"

class LevelState : public IState
{
public:

	LevelState();
	~LevelState();

	void Init(sf::RenderWindow* hwnd_, Input* input_, StateManager* state_manager_);
	void CleanUp();

	bool HandleInput();
	bool Update(float frame_time_);
	void Render();

private:
	sf::View initialView;

	Player* player;
	TileMap tileMap;
};