#pragma once
#include "..\include\SplashState.h"
#include "..\include\MenuState.h"
#include "..\include\LevelState.h"
#include "..\include\OptionsState.h"
#include "..\include\LobbyState.h"

//Forward declaring SFML classes
namespace sf
{
	class RenderWindow;
}

//Forward declaring my own classes
class Input;
class IState;
class Client;

class StateManager
{
public:

	enum States { SPLASH, MENU, LOBBY, LEVEL, OPTIONS};

	StateManager(sf::RenderWindow* hwnd_, Input* input_);
	~StateManager();

	void changeState(States state_);
	IState* getCurrentState();

	void setClientPtr(Client* client_);

private:

	int score;
	bool victory;

	sf::RenderWindow* window;
	Input* input;
	IState* current_state;

	//State Objects
	SplashState splash_state;
	MenuState menu_state;
	LevelState level_state;
	OptionsState options_state;
	LobbyState lobby_state;
};