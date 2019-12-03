#include "..\include\Client.h"

#include <thread>
#include "..\include\StateManager.h"
#include "..\include\Bullet.h"

Client::Client() : ready(false), client_ID(-1), num_peers(0), tick(0), dt(0), change_to_level(false), lobby_mode(true), game_time(0)
{
}

Client::~Client()
{
}

bool Client::Update()
{
	float dt = clock.restart().asSeconds();
	tick += dt;

	ReceiveMessage();

	if (tick >= 1 / 64.f)
	{
		SendUpdate();
		tick = 0;
	}

	if (change_to_level)
	{
		change_to_level = false;
		return false;
	}

	return true;
}

bool Client::Update(sf::Vector2f position_)
{
	position = position_;

	float dt = clock.restart().asSeconds();
	tick += dt;
	game_time += dt;

	ReceiveMessage();

	if (tick >= 1 / 64.f)
	{
		SendUpdate();
		tick = 0;
	}

	for (auto current : peers)
	{
		current.second->updateSprite(dt);
		current.second->cleanMessages();
		if (!current.second->getRecievedThisFrame() && !current.second->getLerping())
		{
			current.second->predictPosition(game_time);
		}
		
		if (current.second->getLerping())
		{
			sf::Vector2f next_pos;
			next_pos = lerp(current.second->getPosition(), current.second->getLerpTarget(), current.second->lerp_t_val += 0.05);
			current.second->setPosition(next_pos);
			
			if (current.second->getPosition() == current.second->getLerpTarget() || current.second->lerp_t_val == 1)
			{
				current.second->setLerping(false);
			}
			//if ((current.second->getPosition().x <= current.second->getLerpTarget().x + 0.5) && (current.second->getPosition().x >= current.second->getLerpTarget().x - 0.5)  && (current.second->getPosition().y <= current.second->getLerpTarget().y + 0.5) && (current.second->getPosition().y >= current.second->getLerpTarget().y- 0.5))
			//{
			//	current.second->setLerping(false);
			//}
		}

		current.second->setRecievedThisFrame(false);

	}

	return true;
}

void Client::Init(StateManager* state_manager_)
{
	state_manager = state_manager_;
	
	local_addr = "127.0.0.1";
	server_addr = "127.0.0.1";
	server_port = 4444;

	if (local_sock.bind(sf::Socket::AnyPort, local_addr) != sf::Socket::Done)
	{
		std::printf("Socket did not bind\n");
	}
	local_port = local_sock.getLocalPort();

	// Join by pinging server
	JoinServer(&local_sock, server_addr, server_port);
}

void Client::disconnect()
{
	sf::Packet disconnect_packet;
	disconnect_packet << MessageType::PLAYER_DISCONNECT;
	disconnect_packet << client_ID;
	
	local_sock.send(disconnect_packet, server_addr, server_port);
}

bool Client::getReady()
{
	return ready;
}

void Client::toggleReady()
{
	ready = !ready;
}

void Client::sendBulletInfo(sf::Vector2f start_pos_, sf::Vector2f velocity_, float rotation_angle_)
{
	sf::Packet bullet_packet;

	bullet_packet << MessageType::NEW_BULLET;

	bullet_packet << client_ID;

	bullet_packet << start_pos_.x;
	bullet_packet << start_pos_.y;

	bullet_packet << velocity_.x;
	bullet_packet << velocity_.y;

	bullet_packet << rotation_angle_;

	sf::Socket::Status send_error;
	send_error = local_sock.send(bullet_packet, server_addr, server_port);


}

int Client::getID()
{
	return client_ID;
}

std::vector<Bullet*> Client::getBullets()
{
	return bullets;
}

void Client::clearBullets()
{
	bullets.clear();
}

std::map<int, Peer*> Client::getPeers()
{
	return peers;
}

void Client::JoinServer(sf::UdpSocket* sock_, sf::IpAddress addr_, unsigned short port_)
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
				
				if (temp_peer_ID != client_ID)
				{
					Peer* temp_peer = new Peer();
					temp_peer->setID(temp_peer_ID);
					temp_peer->setPosition(sf::Vector2f(100, 100));
					printf("join server %i\n", temp_peer_ID);
					peers.insert(std::pair<int, Peer*>(temp_peer_ID, temp_peer));
				}
				
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

void Client::ReceiveMessage()
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
			if (temp_peer_ID != client_ID)
			{
				new_peer->setID(temp_peer_ID);
				printf("NEW_CONNECTION %i\n", temp_peer_ID);
				peers.insert(std::pair<int, Peer*>(temp_peer_ID, new_peer));
			}
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
	case PLAYER_UPDATE:
	{
		int temp_num;
		sf::Vector2f temp_position;

		recv_pack >> temp_num;
		num_peers = temp_num;

		for (int i = 0; i < num_peers; i++)
		{
			int temp_ID;
			recv_pack >> temp_ID;

			float temp_time;
			recv_pack >> temp_time;
			recv_pack >> temp_position.x;
			recv_pack >> temp_position.y;

			if (peers.find(temp_ID) != peers.end() && temp_ID != client_ID)
			{
				if (peers[temp_ID]->getLastPackeTime() <= temp_time)
				{
					if (peers[temp_ID]->getPosition() != temp_position)
					{
						peers[temp_ID]->setLerping(true);
						peers[temp_ID]->setLerpTarget(temp_position);
						peers[temp_ID]->lerp_t_val = 0;
					}
					else
					{
						peers[temp_ID]->setPosition(temp_position);
					}
					peers[temp_ID]->storeMessage(temp_position.x, temp_position.y, temp_time);
					peers[temp_ID]->setRecievedThisFrame(true);
					peers[temp_ID]->setLastPacketTime(temp_time);
				}
				else
				{
					printf("Out of order update from ID %i\n", temp_ID);
				}
			}
		}

		unsigned int num_bullets;
		recv_pack >> num_bullets;

		for (int i = 0; i < num_bullets; i++)
		{
			Bullet* temp_bullet = new Bullet();
			sf::Vector2f temp_pos;
			sf::Vector2f temp_velocity;
			float temp_angle;
			int temp_ID;

			recv_pack >> temp_ID;

			recv_pack >> temp_pos.x;
			recv_pack >> temp_pos.y;

			recv_pack >> temp_velocity.x;
			recv_pack >> temp_velocity.y;

			recv_pack >> temp_angle;

			temp_bullet->setPosition(temp_pos);
			temp_bullet->setVelocity(temp_velocity);
			temp_bullet->setRotation(temp_angle);

			temp_bullet->setAlive(true);

			if (temp_ID != client_ID)
			{
				temp_bullet->setIsEnemy(true);
				bullets.push_back(temp_bullet);
			}

			//printf("recv ID: %i pos: %f , %f vel: %f , %f angle: %f\n", temp_ID, temp_bullet->getPosition().x, temp_bullet->getPosition().y, temp_bullet->getVelocity().x, temp_bullet->getVelocity().y, temp_bullet->getRotation());
		}

		break;
	}
	case PLAYER_DISCONNECT:
	{
		int temp_ID;

		recv_pack >> temp_ID;

		peers.erase(temp_ID);

		break;
	}
	case LOBBY_UPDATE:
	{
		int temp_num;
		bool temp_ready;

		recv_pack >> temp_num;
		num_peers = temp_num;

		for (int i = 0; i < num_peers; i++)
		{
			int temp_ID;
			recv_pack >> temp_ID;

			recv_pack >> temp_ready;
			if (peers.find(temp_ID) != peers.end() && temp_ID != client_ID)
			{
				peers[temp_ID]->setReady(temp_ready);
			}
			
		}

		break;
	}
	case GAME_STARTING:
	{
		change_to_level = true;
		lobby_mode = false;
		for (auto current : peers)
		{
			current.second->setUpTexture();
		}
		game_time = 0;
		break;
	}
	case NEW_CONNECT_REJECT:
	{
		state_manager->changeState(StateManager::MENU);
		break;
	}
	case ADD_PEER:
	{
		Peer* temp_peer = new Peer();
		int temp_id;
		recv_pack >> temp_id;
		temp_peer->setID(temp_id);
		temp_peer->setReady(false);
		temp_peer->setPosition(sf::Vector2f(100, 100));
		printf("ADD_PEER %i\n", temp_id);
		peers.insert(std::pair<int, Peer*>(temp_id, temp_peer));

		break;
	}
	default:
	{
		break;
	}
	}
}

void Client::SendUpdate()
{
	sf::Socket::Status connection_status = sf::Socket::Status::Done;
	sf::Socket::Status send_error;

	if (lobby_mode)
	{
		sf::Packet lobby_update_packet;
		lobby_update_packet << MessageType::LOBBY_UPDATE;
		lobby_update_packet << client_ID;
		lobby_update_packet << ready;

		send_error = local_sock.send(lobby_update_packet, server_addr, server_port);
	}
	else
	{
		sf::Packet game_update_packet;
		game_update_packet << MessageType::PLAYER_UPDATE;
		game_update_packet << game_time;
		game_update_packet << client_ID;
		game_update_packet << position.x;
		game_update_packet << position.y;

		send_error = local_sock.send(game_update_packet, server_addr, server_port);
	}
	

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

			JoinServer(&local_sock, server_addr, server_port);

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

sf::Vector2f Client::lerp(sf::Vector2f a, sf::Vector2f b, float t)
{
	return a * (1 - t) + b * t;
}
