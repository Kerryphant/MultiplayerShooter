#include "..\include\MenuState.h"
#include "..\include\StateManager.h"
#include "..\include\Input.h"


MenuState::MenuState()
{
	background_texture.loadFromFile("Media/Sprites/MenuBackground.png");

	background_shape.setTexture(&background_texture);
	background_shape.setSize(sf::Vector2f(960, 600));
	background_shape.setPosition(0, 0);

	menu_view.setCenter(480, 300);
	menu_view.setSize(sf::Vector2f(960, 600));
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

	sf::Socket::Status status = socket.connect("127.0.0.1", 5555);

	if (status != sf::Socket::Done)
	{
		printf("client failed to connect");
	}
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

	return true;
}

bool MenuState::Update(float frame_time)
{
	char data[5] = {'h', 'e', 'l', 'l', 'o'};

	// TCP socket:
	sf::Socket::Status error = socket.send(data, 5);
	
	if (error != sf::Socket::Done)
	{
		printf("sending failed\n");
		switch (error)
		{
		case sf::Socket::NotReady:
			printf("Socket not ready\n");
			break;
		case sf::Socket::Partial:
			printf("Socket partial\n");
			break;
		case sf::Socket::Disconnected:
			printf("Socket disconnected\n");
			break;
		case sf::Socket::Error:
			printf("Socket ERROR\n");
			break;
		default:
			break;
		}
	}

	return true;
}

void MenuState::Render()
{
	//Beginning of drawing
	window->clear(sf::Color::Black);

	window->draw(background_shape);

	window->display();
	//End of drawing
}