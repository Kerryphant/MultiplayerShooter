#pragma once
#include <SFML/Graphics.hpp>
#include "..\include\Animation.h"
#include "..\include\Sprite.h"

class Peer
{
public:

	Peer();
	~Peer();

	int getID();
	void setID(int ID_);

	bool getReady();
	void setReady(bool ready_);

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f position_);

	void setUpTexture();
	void updateSprite(float frame_time_);
	Sprite getShape();

	float getLastPackeTime();
	void setLastPacketTime(float time_);

	void predictPosition(float gameTime_);
	void storeMessage(float x_, float y_, float time_);
	void cleanMessages();

	bool getRecievedThisFrame();
	void setRecievedThisFrame(bool toggle_);

	void setLerping(bool toggle_);
	bool getLerping();

	sf::Vector2f getLerpTarget();
	void setLerpTarget(sf::Vector2f target_);

	float lerp_t_val;

private:

	struct Message
	{
		float x;
		float y;
		float time;
	};

	std::vector<Message> stored_messages;
	bool position_lerping;
	sf::Vector2f lerp_target;

	int ID;
	float last_packet_time;
	bool received_this_frame;
	bool ready;
	sf::Vector2f position;

	bool flipped;
	sf::Texture texture;
	Sprite sprite;

	Animation* current_animation;
	Animation walk;
	Animation stand;
};