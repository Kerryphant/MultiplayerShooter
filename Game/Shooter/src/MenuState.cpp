#include "..\include\MenuState.h"
#include "..\include\StateManager.h"
#include "..\include\Input.h"
#include "..\include\Button.h"


MenuState::MenuState()
{
	background_texture.loadFromFile("Media/Sprites/MenuBackground.png");

	background_shape.setTexture(&background_texture);
	background_shape.setSize(sf::Vector2f(960, 600));
	background_shape.setPosition(0, 0);

	menu_view.setCenter(480, 300);
	menu_view.setSize(sf::Vector2f(960, 600));

	int button_spacing = 130;
	for (int i = 0; i < 2; i++)
	{
		buttons[i] = new Button(280, 150 + (button_spacing * i));
	}
	
}

MenuState::~MenuState()
{
}

void MenuState::Init(sf::RenderWindow* hwnd_, Input* input_, StateManager* state_manager_)
{
	window = hwnd_;
	window->setView(menu_view);

	input_handler = input_;
	state_manager = state_manager_;

	buttons[0]->setSprite("Media/Sprites/Menu/SoloButton.png");
	buttons[0]->setAction([&]() -> void
	{
		state_manager->changeState(StateManager::LOBBY);
	}
	);

	//exit button
	buttons[1]->setSprite("Media/Sprites/Menu/ExitButton.png");
	buttons[1]->setAction([&]() -> void
	{
		window->close();
	}
	);
}

void MenuState::CleanUp()
{
	window = nullptr;
	input_handler = nullptr;
	state_manager = nullptr;
}

bool MenuState::HandleInput()
{
	if (input_handler->isKeyDown(sf::Keyboard::Escape))
	{
		//exit the program
		window->close();
	}

	if (input_handler->isMouseLeftDown())
	{
		//set to false to avoid mutiple clicks. We do this at the start in case of a state switch inside the for loop
		input_handler->setMouseLeftDown(false);

		//check all buttons for a click and take action
		for(int i = 0; i < 2; i++)
		{
			buttons[i]->checkClick(cursor.getPosition().x, cursor.getPosition().y);
		}
		
	}

	return true;
}

bool MenuState::Update(unsigned int w_, unsigned int h_, float frame_time_)
{
	cursor.update(input_handler);

	return true;
}

void MenuState::Render()
{
	//Beginning of drawing
	window->clear(sf::Color::Black);

	window->draw(background_shape);

	for (int i = 0; i < 2; i++)
	{
		window->draw(*buttons[i]);
	}

	window->draw(cursor);

	window->display();
	//End of drawing
}