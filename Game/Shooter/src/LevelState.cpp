#include "..\include\LevelState.h"
#include "..\include\StateManager.h"
#include "..\include\Input.h"

LevelState::LevelState()
{
	//100,100 is the position at which the character is first drawn at. Used to prevent a jump in view
	initialView.setCenter(100, 100);
	initialView.setSize(sf::Vector2f(960, 600));

	tileMap.loadMapFile("media/maps/map.txt");
	tileMap.setMap();

	bullet_manager = new BulletManager();

	sf::Mouse::setPosition(sf::Vector2i(0, 0));
	cursor.changeTexture(Cursor::TARGET);
}

LevelState::~LevelState()
{
}

void LevelState::Init(sf::RenderWindow* hwnd_, Input* input_, StateManager* state_manager_)
{
	window = hwnd_;
	window->setView(initialView);
	tileMap.setWindow(window);

	input_handler = input_;
	state_manager = state_manager_;

	player = new Player(input_handler, client->getID());
	player->setAlive(true);

	for (auto current : client->getPeers())
	{
		current.second->setUpTexture();
	}
}

void LevelState::CleanUp()
{
	window = nullptr;
	input_handler = nullptr;
	state_manager = nullptr;
}

bool LevelState::HandleInput()
{
	if (input_handler->isKeyDown(sf::Keyboard::Escape))
	{
		//exit the program
		window->close();
	}

	//if the player shoots
	if (input_handler->isMouseLeftDown())
	{
		bullet_manager->createNewBullet(cursor.getPosition(), player->getPosition(), client);
		input_handler->setMouseLeftDown(false);
	}

	return true;
}

bool LevelState::Update(unsigned int w_, unsigned int h_, float frame_time_)
{
	//cursor.update(input_handler);
	cursor.setPosition(player->getPosition().x + input_handler->getMouseX() - (w_ / 2.0f), player->getPosition().y + input_handler->getMouseY() - (h_ / 2.0f));

	player->update(frame_time_);
	player->handleInput(frame_time_, window);

	bullet_manager->updateBullets(frame_time_, client);

	client->Update(player->getPosition());

	return true;
}

void LevelState::Render()
{
	//Beginning of drawing
	window->clear(sf::Color::Black);
	
	tileMap.drawMap();
	window->draw(*player);

	std::map<int, Peer*> temp_peers = client->getPeers();

	for (auto current_peer : temp_peers)
	{
		if (current_peer.second->getID() >= 0 && current_peer.second->getID() != client->getID())
		{	
			window->draw(current_peer.second->getShape());
		}
	}

	bullet_manager->renderBullets(window);

	window->draw(cursor);

	window->display();
	//End of drawing
}

void LevelState::setClientPtr(Client* client_)
{
	client = client_;
}
