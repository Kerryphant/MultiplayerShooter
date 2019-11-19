#include "..\include\LevelState.h"
#include "..\include\StateManager.h"
#include "..\include\Input.h"

LevelState::LevelState()
{
	//100,100 is the position at which the character is first drawn at. Used to prevent a jump in view
	initialView.setCenter(100, 100);
	initialView.setSize(sf::Vector2f(960, 600));

	tileMap.loadMapFile("media/maps/map.txt");
	tileMap.setMap();
}

LevelState::~LevelState()
{
}

void LevelState::Init(sf::RenderWindow* hwnd_, Input* input_, StateManager* state_manager_)
{
	window = hwnd_;
	window->setView(initialView);
	tileMap.setWindow(window);

	input_handler = input_;
	state_manager = state_manager_;

	player = new Player(input_handler);
}

void LevelState::CleanUp()
{
	window = nullptr;
	input_handler = nullptr;
	state_manager = nullptr;
}

bool LevelState::HandleInput()
{
	if (input_handler->isKeyDown(sf::Keyboard::Escape))
	{
		//exit the program
		window->close();
	}

	return true;
}

bool LevelState::Update(float frame_time_)
{
	player->update(frame_time_);
	player->handleInput(frame_time_, window);

	return true;
}

void LevelState::Render()
{
	//Beginning of drawing
	window->clear(sf::Color::Black);
	
	tileMap.drawMap();
	window->draw(*player);


	window->display();
	//End of drawing
}