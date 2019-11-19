#include "..\include\LobbyState.h"
#include "..\include\StateManager.h"
#include "..\include\Input.h"
#include "..\include\Button.h"
#include <thread>

LobbyState::LobbyState() : ready(false), client_ID(-1), num_peers(0), tick(0), dt(0)
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

	local_addr = "127.0.0.1";
	server_addr = "127.0.0.1";
	server_port = 4444;

	ready_button->setSprite("Media/Sprites/ReadyButton.png");
	ready_button->setAction([&]() -> void
	{
		ready = !ready;
		printf("Ready toggled\n");
	}
	);
	ready_button->setSize(sf::Vector2f(200,50));

	//sf::Socket::Status status = socket.connect("127.0.0.1", 5555);
	if (local_sock.bind(sf::Socket::AnyPort, local_addr) != sf::Socket::Done)
	{
		std::printf("Socket did not bind\n");
	}
	local_port = local_sock.getLocalPort();

	// Join by pinging server
	joinServer(&local_sock, server_addr, server_port);
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

	float dt = clock.restart().asSeconds();
	tick += dt;

	receiveMessage();

	if (tick >= 1 / 64.f)
	{
		sendUpdate();
		tick = 0;
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
	
	for (auto current_peer : peers)
	{
		if (current_peer.second->getID() == client_ID)
		{
			if (ready)
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

void LobbyState::joinServer(sf::UdpSocket* sock_, sf::IpAddress addr_, unsigned short port_)
{
	sf::Packet join_info;
	
	join_info << MessageType::NEW_CONNECTION;
	
	bool connected = false;
	int retry_count = 0;

	while (!connected && retry_count < 10)
	{
		if (sock_->send(join_info, addr_, port_) != sf::Socket::Done)
		{
			printf("client failed to connect. Waiting 2 seconds before trying again\n");
			std::this_thread::sleep_for(std::chrono::seconds(2));
			retry_count++;
		}
		else
		{
			printf("sent request to server\n");
			connected = true;
		}
	}
	
	if (connected)
	{
		printf("sent to server successfully\n");
		sf::Packet new_connection_pack;
		sf::IpAddress recv_addr;
		unsigned short recv_port;

		sf::Socket::Status send_error = local_sock.receive(new_connection_pack, server_addr, server_port);

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
				printf("Socket disconnected.\n");

				break;
			case sf::Socket::Error:
				printf("Socket ERROR\n");
				break;
			default:
				break;
			}
		}
		else
		{
			printf("got info from server\n");
			
			int message_type;

			new_connection_pack >> message_type;

			if (message_type != MessageType::NEW_CONNECTION)
			{
				printf("weird info from server. Returning to menu\n");
				state_manager->changeState(StateManager::MENU);
			}

			new_connection_pack >> client_ID;
			new_connection_pack >> num_peers;
			for (int i = 0; i < num_peers; i++)
			{
				int temp_peer_ID;
				new_connection_pack >> temp_peer_ID;
				Peer* temp_peer = new Peer();
				temp_peer->setID(temp_peer_ID);
				peers.insert(std::pair<int, Peer*>(temp_peer_ID, temp_peer));
			}

			local_sock.setBlocking(false);
			printf("set to non-blocking\n");
		}
		
	}
	else
	{
		printf("failed to connect to server. Returning to menu state\n");
		state_manager->changeState(StateManager::MENU);
	}
	

	return;
}

void LobbyState::receiveMessage()
{
	sf::Packet recv_pack;
	sf::IpAddress recv_addr;
	unsigned short recv_port;

	if (local_sock.receive(recv_pack, recv_addr, recv_port) != sf::Socket::Done)
	{
		//printf("failed to receive\n");
	}

	int message_type;
	recv_pack >> message_type;

	switch (message_type)
	{
	case NEW_CONNECTION:
	{
		//get this client's ID
		recv_pack >> client_ID;

		//get the number of peers in the lobby
		recv_pack >> num_peers;

		//for the number of peers in the game
		for (int i = 0; i < num_peers; i++)
		{
			//create a new peer
			Peer* new_peer = new Peer;
			int temp_peer_ID;

			//assign it it's ID
			recv_pack >> temp_peer_ID;
			new_peer->setID(temp_peer_ID);
			peers.insert(std::pair<int, Peer*>(temp_peer_ID, new_peer));
		}

		//assign each peer their ready value
		for (int i = 0; i < num_peers; i++)
		{
			bool temp_ready;
			recv_pack >> temp_ready;

			peers[i]->setReady(temp_ready);
		}

		break;
	}
	case GAME_STARTING:
	{
		state_manager->changeState(StateManager::LEVEL);
	}
	case ADD_PEER:
	{
		Peer* temp_peer = new Peer();
		int temp_id;
		recv_pack >> temp_id;
		temp_peer->setID(temp_id);
		temp_peer->setReady(false);

		peers.insert(std::pair<int, Peer*>(temp_id, temp_peer));

		break;
	}
	case LOBBY_UPDATE:
	{
		int temp_num;
		recv_pack >> temp_num;
		std::vector<int> temp_id_order;

		num_peers = temp_num;

		for (int i = 0; i < num_peers; i++)
		{
			int temp_ID;
			recv_pack >> temp_ID;
			temp_id_order.push_back(temp_ID);
		}

		bool temp_ready = false;
		for (int i = 0; i < num_peers; i++)
		{
			recv_pack >> temp_ready;
			peers[temp_id_order[i]]->setReady(temp_ready);
		}

		break;
	}
	case PLAYER_DISCONNECT:
	{

		break;
	}
	default:
	{
		break;
	}
	}
}

void LobbyState::sendUpdate()
{
	sf::Socket::Status connection_status = sf::Socket::Status::Done;

	sf::Packet lobby_update_packet;
	lobby_update_packet << MessageType::LOBBY_UPDATE;
	lobby_update_packet << client_ID;
	lobby_update_packet << ready;

	sf::Socket::Status send_error = local_sock.send(lobby_update_packet, server_addr, server_port);

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

			joinServer(&local_sock, server_addr, server_port);

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
}
