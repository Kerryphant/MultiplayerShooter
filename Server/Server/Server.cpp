#include "Server.h"

#include <chrono>
#include <ctime>   

Server::Server()
{

	if (socket.bind(SERVERPORT) != sf::Socket::Done)
	{
		// error...
	}

	socket.setBlocking(false);
}

Server::~Server()
{
}

void Server::update(sf::RenderWindow* window_)
{
	
	
	sf::Event event;
	while (window_->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window_->close();
		}
	}
	
	//Get the time since the last frame in milliseconds
	float dt = clock.restart().asSeconds();

	tick += dt;

	receiveMessage();

	if (tick >= 1 / 64.f)
	{
		sendClientUpdates(dt);
		tick = 0;
	}
}

void Server::receiveMessage()
{
	sf::Packet recvPack;
	sf::IpAddress recvAddr;
	unsigned short recvPort;

	//check to receive message
	if (socket.receive(recvPack, recvAddr, recvPort) == sf::Socket::Done)
	{
		//There is a message, update the game info (positions ect)
		int message_type;
		recvPack >> message_type;

		switch (message_type)
		{
		case NEW_CONNECTION:
		{
			printf("New connection\n");

			if (num_connected_players <= 8)
			{
				PlayerConnection* new_player = new PlayerConnection();

				new_player->setAddress(recvAddr);
				new_player->setPort(recvPort);
				new_player->setID(num_connected_players);

				num_connected_players++;

				connected_players.insert(std::pair<int, PlayerConnection*>(num_connected_players - 1, new_player));

				//send confirmation to new player
				sf::Packet new_player_pack;
				new_player_pack << MessageType::NEW_CONNECTION;
				new_player_pack << new_player->getID();
				new_player_pack << num_connected_players;
				for (auto current_player : connected_players)
				{
					new_player_pack << current_player.second->getID();
				}

				for (auto current_player : connected_players)
				{
					new_player_pack << current_player.second->getReady();
				}


				if (socket.send(new_player_pack, recvAddr, recvPort) != sf::Socket::Done)
				{
					printf("failed to connect.\n");
				}
				else
				{
					printf("sent connection info to client\n");
				}


				sf::Packet new_peer;
				new_peer << MessageType::ADD_PEER;
				new_peer << new_player->getID();

				for (auto current_player : connected_players)
				{
					if (current_player.second->getID() != new_player->getID())
					{
						if (socket.send(new_peer, current_player.second->getAddress(), current_player.second->getPort()) != sf::Socket::Done)
						{
							printf("failed to tell %i about new peer \n", current_player.second->getID());
						}
						else
						{
							printf("sent new player info to %i \n", current_player.second->getID());
						}
					}
				}

			}
			else
			{
				sf::Packet new_player_pack;
				new_player_pack << MessageType::NEW_CONNECT_REJECT;

				if (socket.send(new_player_pack, recvAddr, recvPort) != sf::Socket::Done)
				{
					printf("failed to connect.\n");
				}
				else
				{
					printf("sent connection info to client\n");
				}
			}

			break;
		}
		case PLAYER_UPDATE:
		{
			int temp_ID;
			sf::Vector2f temp_position;
			
			recvPack >> temp_ID;
			recvPack >> temp_position.x;
			recvPack >> temp_position.y;

			connected_players[temp_ID]->setPosition(temp_position);

			break;
		}
		case PLAYER_DISCONNECT:
		{
			printf("Player disconnected\n");
			break;
		}
		case LOBBY_UPDATE:
		{
			int client_ID;
			bool ready;

			recvPack >> client_ID;
			recvPack >> ready;
			connected_players[client_ID]->setReady(ready);

			//printf("Lobby update. %i is %i\n", client_ID, ready);


			break;
		}
		case NEW_BULLET:
		{
			BulletInfo temp_info;

			recvPack >> temp_info.position.x;
			recvPack >> temp_info.position.y;
			
			recvPack >> temp_info.velocity.x;
			recvPack >> temp_info.velocity.y;

			recvPack >> temp_info.angle;

			bullets.push_back(temp_info);
		}
		default:
			printf("unexpected receive\n");
			break;
		}

	}
	else
	{
		//no message
		//printf("No incoming messages\n");
	}

	//check for game start condition
	if (lobby_mode)
	{
		bool allReady = true;

		for (int i = 0; i < num_connected_players; i++)
		{
			if (connected_players[i]->getReady() == false)
			{
				allReady = false;
			}
		}

		if (allReady && num_connected_players > 1)
		{
			sf::Packet start_packet;
			start_packet << MessageType::GAME_STARTING;

			for (auto current_player : connected_players)
			{
				if (socket.send(start_packet, current_player.second->getAddress(), current_player.second->getPort()) != sf::Socket::Done)
				{
					printf("failed to tell %i to start \n", current_player.second->getID());
				}
				else
				{
					printf("sent start to %i \n", current_player.second->getID());
					lobby_mode = false;
				}
			}
		}
	}
	
}
	
void Server::sendClientUpdates(float dt_)
{
	//if no win condition, send out updates to clients
	if (true)
	{
		//Handle predicting new positions. All clients must be checked before data is sent out
		if (!lobby_mode)
		{
			for (auto current_player : connected_players)
			{
				//if not got position from them this frame
				if (!current_player.second->getRecievedThisFrame())
				{
					//predict position
					current_player.second->predictNewPosition();

					current_player.second->setRecievedThisFrame(false);
				}
			}
		}

		//for each client
		for (auto current_player : connected_players)
		{
			//check for time out
			float time_out_value = 10000;
			if (current_player.second->getLastMessageTime() > time_out_value)
			{
				//disconnect the player
			}

			//send out updates according to mode
			if (lobby_mode)
			{
				//send the player count, ids in order, bool for if ready
				sf::Packet sendPack;

				sendPack << MessageType::LOBBY_UPDATE << num_connected_players;
				for (auto current_player : connected_players)
				{
					sendPack << current_player.second->getID();
				}

				for (auto current_player : connected_players)
				{
					sendPack << current_player.second->getReady();
				}

				for (auto current_player : connected_players)
				{
					if (socket.send(sendPack, current_player.second->getAddress(), current_player.second->getPort()) != sf::Socket::Done)
					{
						printf("lobby update to %i failed \n", current_player.second->getID());
					}
					else
					{
						//printf("sent update to %i \n", current_player.second->getID());
					}
				}


			}
			else
			{
				//send the player ids, positions
				sf::Packet sendPack;

				sendPack << MessageType::PLAYER_UPDATE;
				sendPack << num_connected_players;

				for (auto current_player : connected_players)
				{
					sendPack << current_player.second->getID();
				}

				for (auto current_player : connected_players)
				{
					sendPack << current_player.second->getPosition().x;
					sendPack << current_player.second->getPosition().y;
				}

				sendPack << bullets.size();

				for (auto current_bullet : bullets)
				{
					sendPack << current_bullet.position.x;
					sendPack << current_bullet.position.y;

					sendPack << current_bullet.velocity.x;
					sendPack << current_bullet.velocity.y;

					sendPack << current_bullet.angle;
				}
				
				bullets.clear();

				for (auto current_player : connected_players)
				{
					if (socket.send(sendPack, current_player.second->getAddress(), current_player.second->getPort()) != sf::Socket::Done)
					{
						printf("lobby update to %i failed \n", current_player.second->getID());
					}
				}
			}

		}

	}
}
