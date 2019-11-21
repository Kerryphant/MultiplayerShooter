#pragma once

//SFML forward declarations
namespace sf
{
	class RenderWindow;
}

//Forward declaration of classes in this project
class Input;
class StateManager;

class IState
{
public:

	virtual ~IState() {}

	virtual void Init(sf::RenderWindow* hwnd_, Input* input_, StateManager* state_manager_) = 0;
	virtual void CleanUp() = 0;
	
	virtual bool HandleInput() = 0;
	virtual bool Update(unsigned int w_, unsigned int h_, float frame_time) = 0;
	virtual void Render() = 0;

	//state this_state;

protected:
	sf::RenderWindow* window;
	Input* input_handler;

	StateManager* state_manager;
};