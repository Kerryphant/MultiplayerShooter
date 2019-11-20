#include "..\include\StateManager.h"
#include "..\include\IState.h"
#include "..\include\Client.h"

StateManager::StateManager(sf::RenderWindow* hwnd_, Input* input_) : score(0), victory(0), window(nullptr), input(nullptr), current_state(nullptr)
{
	window = hwnd_;
	input = input_;
	current_state = nullptr;
}

StateManager::~StateManager()
{

}

void StateManager::changeState(States new_state_)
{
	//if current_state is valid
	if (current_state)
	{
		//clean up the current state
		current_state->CleanUp();
	}

	switch (new_state_)
	{
	case StateManager::SPLASH:
		current_state = &splash_state;
		break;
	case StateManager::MENU:
		current_state = &menu_state;
		break;
	case StateManager::LOBBY:
		current_state = &lobby_state;
		break;
	case StateManager::LEVEL:
		current_state = &level_state;
		break;
	case StateManager::OPTIONS:
		current_state = &options_state;
		break;
	default:
		break;
	}

	current_state->Init(window, input, this);
}

IState* StateManager::getCurrentState()
{
	return current_state;
}

void StateManager::setClientPtr(Client* client_)
{
	level_state.setClientPtr(client_);
}
