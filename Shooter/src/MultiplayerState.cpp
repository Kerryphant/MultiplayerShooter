#include "..\include\MultiplayerState.h"
#include "..\include\StateManager.h"
#include "..\include\Input.h"

MultiplayerState::MultiplayerState()
{
	multiplayer_view.setCenter(480, 300);
	multiplayer_view.setSize(sf::Vector2f(960, 600));
}

MultiplayerState::~MultiplayerState()
{
}

void MultiplayerState::Init(sf::RenderWindow* hwnd_, Input* input_, StateManager* state_manager_)
{
	window = hwnd_;
	window->setView(multiplayer_view);

	input_handler = input_;
	state_manager = state_manager_;

	sf::Socket::Status status = socket.connect("127.0.0.1", 5555);

	if (status != sf::Socket::Done)
	{
		printf("client failed to connect");
	}
	else
	{
		printf("connected to server");
	}
}

void MultiplayerState::CleanUp()
{
	window = nullptr;
	input_handler = nullptr;
	state_manager = nullptr;
}

bool MultiplayerState::HandleInput()
{
	if (input_handler->isKeyDown(sf::Keyboard::Escape))
	{
		//exit the program
		window->close();
	}

	return true;
}

bool MultiplayerState::Update(float frame_time_)
{
	//TCP CONNECTION
	char data[5] = {'h', 'e', 'l', 'l', 'o'};

	sf::Socket::Status send_error = socket.send(data, 5);
	sf::Socket::Status connection_status = sf::Socket::Status::Done;
	
	if (send_error != sf::Socket::Done)
	{
		printf("sending failed\n");
		switch (send_error)
		{
		case sf::Socket::NotReady:
			printf("Socket not ready\n");
			break;
		case sf::Socket::Partial:
			printf("Socket partial\n");
			break;
		case sf::Socket::Disconnected:
			printf("Socket disconnected. Attemping to reconnect to server\n");
			
			connection_status = socket.connect("127.0.0.1", 5555);

			if (connection_status != sf::Socket::Done)
			{
				printf("client failed to connect");
			}
			else
			{
				printf("connected to server");
			}

			break;
		case sf::Socket::Error:
			printf("Socket ERROR\n");
			break;
		default:
			break;
		}
	}

	std::size_t received;
	if (socket.receive(data, 5, received) != sf::Socket::Done)
	{
		printf("failed to receive\n");
	}

	printf("Received %i bytes\n", received);
	printf(data);

	return true;
}

void MultiplayerState::Render()
{
	//Beginning of drawing
	window->clear(sf::Color::Black);

	//draw stuffs

	window->display();
	//End of drawing
}