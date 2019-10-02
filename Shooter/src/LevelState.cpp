#include "..\include\LevelState.h"
#include "..\include\StateManager.h"
#include "..\include\Input.h"

LevelState::LevelState()
{
	level_view.setCenter(480, 300);
	level_view.setSize(sf::Vector2f(960, 600));
}

LevelState::~LevelState()
{
}

void LevelState::Init(sf::RenderWindow* hwnd_, Input* input_, StateManager* state_manager_)
{
	window = hwnd_;
	window->setView(level_view);

	input_handler = input_;
	state_manager = state_manager_;
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

bool LevelState::Update(float frame_time)
{
	return true;
}

void LevelState::Render()
{
	//Beginning of drawing
	window->clear(sf::Color::Black);

	//draw stuffs

	window->display();
	//End of drawing
}