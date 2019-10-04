#include "..\include\OptionsState.h"
#include "..\include\StateManager.h"
#include "..\include\Input.h"

OptionsState::OptionsState()
{
	options_view.setCenter(480, 300);
	options_view.setSize(sf::Vector2f(960, 600));
}

OptionsState::~OptionsState()
{
}

void OptionsState::Init(sf::RenderWindow* hwnd_, Input* input_, StateManager* state_manager_)
{
	window = hwnd_;
	window->setView(options_view);

	input_handler = input_;
	state_manager = state_manager_;
}

void OptionsState::CleanUp()
{
	window = nullptr;
	input_handler = nullptr;
	state_manager = nullptr;
}

bool OptionsState::HandleInput()
{
	if (input_handler->isKeyDown(sf::Keyboard::Escape))
	{
		//exit the program
		window->close();
	}

	return true;
}

bool OptionsState::Update(float frame_time_)
{
	return true;
}

void OptionsState::Render()
{
	//Beginning of drawing
	window->clear(sf::Color::Black);

	//draw stuffs

	window->display();
	//End of drawing
}