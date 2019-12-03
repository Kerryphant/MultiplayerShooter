#include "..\include\Peer.h"

Peer::Peer() : flipped(false), current_animation(nullptr), ID(-1), ready(false), last_packet_time(0), position_lerping(false), lerp_t_val(0)
{
	sprite.setSize(sf::Vector2f(51, 64));
	sprite.setPosition(100, 100);

	//each frame is 51 wide, 64 tall
	walk.addFrame(sf::IntRect(0, 0, 51, 64));
	walk.addFrame(sf::IntRect(51, 0, 51, 64));
	walk.addFrame(sf::IntRect(102, 0, 51, 64));
	walk.addFrame(sf::IntRect(153, 0, 51, 64));
	walk.addFrame(sf::IntRect(204, 0, 51, 64));
	walk.addFrame(sf::IntRect(255, 0, 51, 64));
	walk.addFrame(sf::IntRect(306, 0, 51, 64));
	walk.addFrame(sf::IntRect(357, 0, 51, 64));

	walk.setFrameSpeed(1.f / 10.f);

	stand.addFrame(sf::IntRect(0, 66, 51, 64));
	stand.addFrame(sf::IntRect(51, 66, 51, 64));

	stand.setFrameSpeed(3.f / 10.f);

	current_animation = &stand;
}

Peer::~Peer()
{
}

int Peer::getID()
{
	return ID;
}

void Peer::setID(int ID_)
{
	ID = ID_;
}

bool Peer::getReady()
{
	return ready;
}

void Peer::setReady(bool ready_)
{
	ready = ready_;
}

sf::Vector2f Peer::getPosition()
{
	return position;
}

void Peer::setPosition(sf::Vector2f position_)
{
	position = position_;
	sprite.setPosition(position_);
}

void Peer::setUpTexture()
{
	std::string path = "Media/Sprites/Character/";
	path += std::to_string(ID);
	path += "Char.png";

	sprite.createTexture(path);
	 
	sprite.setTextureRect(current_animation->getCurrentFrame());
	sprite.setPosition(position);

	sprite.setCollisionBox(sprite.getPosition().x, sprite.getPosition().y, 51, 64);
}

void Peer::updateSprite(float frame_time_)
{
	current_animation->animate(frame_time_);

	sprite.setTextureRect(current_animation->getCurrentFrame());
	stand.setFlipped(flipped);
	current_animation = &stand;

	sprite.updateCollisionBox();
}

Sprite Peer::getShape()
{
	return sprite;
}

float Peer::getLastPackeTime()
{
	return last_packet_time;
}

void Peer::setLastPacketTime(float time_)
{
	last_packet_time = time_;
}

void Peer::predictPosition(float gameTime_)
{
	float predictedX = getPosition().x;
	float predictedY = getPosition().y;

	const int msize = stored_messages.size();
	if (msize < 3) 
	{
		setPosition(sf::Vector2f(predictedX, predictedY));
	}
	else
	{
		const Message& msg0 = stored_messages[msize - 1];
		const Message& msg1 = stored_messages[msize - 2];
		const Message& msg2 = stored_messages[msize - 3];

		// FIXME: Implement prediction here!
		// You have:
		// - the history of position messages received, in "m_Messages"
		//   (msg0 is the most recent, msg1 the 2nd most recent, msg2 the 3rd most recent)
		// - the current time, in "gameTime"
		//
		// You need to update:
		// - the predicted position at the current time, in "predictedX" and "predictedY"

		//v = change in pos / change in time
		if(msg1.time - msg0.time)
		{
			float xVel = (msg1.x - msg0.x) / (msg1.time - msg0.time);
			float yVel = (msg1.y - msg0.y) / (msg1.time - msg0.time);

			predictedX = msg0.x + xVel;
			predictedY = msg0.y + yVel;
		}

		//printf("%i predicted position: %f , %f \n", ID, predictedX, predictedY);

		setPosition(sf::Vector2f(predictedX, predictedY));
	}
}

void Peer::storeMessage(float x_, float y_, float time_)
{
	Message new_message;
	new_message.x = x_;
	new_message.y = y_;
	new_message.time = time_;
	
	stored_messages.push_back(new_message);
}

void Peer::cleanMessages()
{
	if (stored_messages.size() > 4)
	{
		stored_messages.erase(stored_messages.begin());
	}
}

bool Peer::getRecievedThisFrame()
{
	return received_this_frame;
}

void Peer::setRecievedThisFrame(bool toggle_)
{
	received_this_frame = toggle_;
}

void Peer::setLerping(bool toggle_)
{
	position_lerping = toggle_;
}

bool Peer::getLerping()
{
	return position_lerping;
}

sf::Vector2f Peer::getLerpTarget()
{
	return lerp_target;
}

void Peer::setLerpTarget(sf::Vector2f target_)
{
	lerp_target = target_;
}
