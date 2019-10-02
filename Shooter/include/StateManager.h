#pragma once
#include "..\include\SplashState.h"
#include "..\include\MenuState.h"
#include "..\include\LevelState.h"

//Forward declaring SFML classes
namespace sf
{
	class RenderWindow;
}

//Forward declaring my own classes
class Input;
class IState;

class StateManager
{
public:

	enum States { LEVEL, MENU, SPLASH, END, CONTROLS};

	StateManager(sf::RenderWindow* hwnd_, Input* input_);
	~StateManager();

	void changeState(States state_);
	IState* getCurrentState();



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
};