#include "..\include\LobbyState.h"
#include "..\include\StateManager.h"
#include "..\include\Input.h"
#include "..\include\Button.h"


LobbyState::LobbyState()
{
	background_texture.loadFromFile("Media/Sprites/MenuBackground.png");

	ready_texture.loadFromFile("Media/Sprites/ReadyButton2.png");
	unready_texture.loadFromFile("Media/Sprites/ReadyButton.png");

	background_shape.setTexture(&background_texture);
	background_shape.setSize(sf::Vector2f(960, 600));
	background_shape.setPosition(0, 0);
	
	ready_shape.setTexture(&unready_texture);
	ready_shape.setSize(sf::Vector2f(200, 50));
	ready_shape.setPosition(sf::Vector2f(660, 220));

	multiplayer_view.setCenter(480, 300);
	multiplayer_view.setSize(sf::Vector2f(960, 600));

	ready_button = new Button(660, 120);

	client = new Client();
}

LobbyState::~LobbyState()
{
}

void LobbyState::Init(sf::RenderWindow* hwnd_, Input* input_, StateManager* state_manager_)
{
	window = hwnd_;
	window->setView(multiplayer_view);

	input_handler = input_;
	state_manager = state_manager_;

	
	client->Init(state_manager);

	ready_button->setSprite("Media/Sprites/ReadyButton.png");
	ready_button->setAction([&]() -> void
	{
		client->toggleReady();
		printf("Ready toggled\n");
	}
	);
	ready_button->setSize(sf::Vector2f(200,50));
}

void LobbyState::CleanUp()
{
	window = nullptr;
	input_handler = nullptr;
	state_manager = nullptr;
}

bool LobbyState::HandleInput()
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
		ready_button->checkClick(cursor.getPosition().x, cursor.getPosition().y);
	}

	return true;
}

bool LobbyState::Update(float frame_time_)
{
	cursor.update(input_handler);

	if (!client->Update())
	{
		state_manager->setClientPtr(client);
		state_manager->changeState(StateManager::LEVEL);
	}

	return true;
}

void LobbyState::Render()
{
	//Beginning of drawing
	window->clear(sf::Color::Black);

	window->draw(background_shape);

	int ready_spacing = 60;
	int count = 0;
	sf::Vector2i starting_pos(660, 190);
	
	std::map<int, Peer*> temp_peers = client->getPeers();

	for (auto current_peer : temp_peers)
	{
		if (current_peer.second->getID() == client->getID())
		{
			if (client->getReady())
			{
				ready_button->setSprite("Media/Sprites/ReadyButton2.png");
				window->draw(*ready_button);
			}
			else
			{
				ready_button->setSprite("Media/Sprites/ReadyButton.png");
				window->draw(*ready_button);
			}
		}
		else
		{
			if (current_peer.second->getReady())
			{
				ready_shape.setTexture(&ready_texture);
			}
			else
			{
				ready_shape.setTexture(&unready_texture);
			}
			
			ready_shape.setPosition(sf::Vector2f(starting_pos.x, starting_pos.y + (ready_spacing * count)));
			window->draw(ready_shape);
			count++;
		}
		
		

	}

	window->draw(cursor);

	window->display();
	//End of drawing
}

