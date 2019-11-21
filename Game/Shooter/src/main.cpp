#include <SFML/Graphics.hpp>

#include "..\include\Input.h"
#include "..\include\StateManager.h"
#include "..\include\IState.h"


void main()
{
	//window dimensions
	unsigned int width = 960;
	unsigned int height = 600;

	// Create window
	sf::RenderWindow window(sf::VideoMode(width, height), "Shooter Game", sf::Style::Close);

	//Input object
	Input input;
	//Set to false as previously appeared to default true
	input.setMouseLeftDown(false);

	//statemanager
	StateManager state_manager(&window, &input);
	//setting initial state to splashscreen
	state_manager.changeState(StateManager::SPLASH);

	//Delta time
	sf::Clock clock;
	float delta_time;

	//so we can draw cursor sprite
	window.setMouseCursorVisible(false);

	// Game loop
	while (window.isOpen())
	{

		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:

				width = event.size.width;
				height = event.size.height;

				break;
			case sf::Event::KeyPressed:
				// update input class
				input.setKeyDown(event.key.code);
				break;
			case sf::Event::KeyReleased:
				//update input class
				input.setKeyUp(event.key.code);
				break;
			case sf::Event::MouseMoved:
				//update input class
				input.setMousePosition(event.mouseMove.x, event.mouseMove.y);
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					input.setMouseLeftDown(true);
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					input.setMouseLeftDown(false);
				}
				break;
			default:
				// don't handle other events
				break;
			}

		}

		//Calculate delta time (how much time has passed)
		delta_time = clock.restart().asSeconds();

		//combined contains handle input, update, and render functions in that order
		state_manager.getCurrentState()->HandleInput();
		state_manager.getCurrentState()->Update(width, height, delta_time);
		state_manager.getCurrentState()->Render();
	}


}
