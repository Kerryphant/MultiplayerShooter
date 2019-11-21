#include "..\include\SplashState.h"
#include "..\include\Input.h"
#include "..\include\StateManager.h"
#include <thread>


SplashState::SplashState()
{
	//this_state = SPLASH;

	background_texture.loadFromFile("Media/Sprites/SplashScreen.png");

	background_shape.setTexture(&background_texture);
	background_shape.setSize(sf::Vector2f(960, 600));
	background_shape.setPosition(0, 0);

	splash_view.setCenter(480, 300);
	splash_view.setSize(sf::Vector2f(960, 600));
}

SplashState::~SplashState()
{
}

void SplashState::Init(sf::RenderWindow* hwnd_, Input* input_, StateManager* state_manager_)
{
	window = hwnd_;
	window->setView(splash_view);

	input_handler = input_;
	state_manager = state_manager_;
}

void SplashState::CleanUp()
{
	window = nullptr;
	input_handler = nullptr;
	state_manager = nullptr;
}

bool SplashState::HandleInput()
{
	//if the user pressed the escape key
	if (input_handler->isKeyDown(sf::Keyboard::Escape))
	{
		//exit the program
		window->close();
	}

	return true;
}

bool SplashState::Update(unsigned int w_, unsigned int h_, float frame_time_)
{
	

	return true;
}

void SplashState::Render()
{
	//Beginning of drawing
	window->clear(sf::Color::Black);

	window->draw(background_shape);

	window->display(); 
	//End of drawing

	std::this_thread::sleep_for(std::chrono::seconds(2));
	state_manager->changeState(StateManager::MENU);
}
