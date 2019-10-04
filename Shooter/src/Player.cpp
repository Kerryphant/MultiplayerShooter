#include "..\include\Player.h"

Player::Player(Input* input_) : Sprite(), health(100), move_speed(300.f), flipped(false), current_animation(nullptr)
{
	input = input_;

	texture.loadFromFile("Media/Sprites/Character/CharacterSpriteSheet.png");

	setTexture(&texture);
	setSize(sf::Vector2f(51, 64));
	setPosition(100, 100);

	setCollisionBox(this->getPosition().x, this->getPosition().y, 51, 64);

	player_camera.setCenter(this->getPosition());
	player_camera.setSize(sf::Vector2f(960, 600));

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

Player::~Player()
{
}

void Player::update(float frame_time_)
{
	if (health <= 0) 
	{
		alive = false;
	}

	current_animation->animate(frame_time_);

	setTextureRect(current_animation->getCurrentFrame());
	stand.setFlipped(flipped);
	current_animation = &stand;

	updateCollisionBox();
}

void Player::handleInput(float frame_time_, sf::RenderWindow* window_)
{
	if (input->isKeyDown(sf::Keyboard::W))
	{
		//move up	
		move(0, -(move_speed * frame_time_));

		//move the view
		player_camera.setCenter(this->getPosition());
		window_->setView(player_camera);

		current_animation = &walk;
		setTextureRect(current_animation->getCurrentFrame());
	}

	if (input->isKeyDown(sf::Keyboard::A))
	{
		float moveAmount = -(move_speed * frame_time_);
		//move left
		move(moveAmount, 0);

		//move the view
		player_camera.setCenter(this->getPosition());
		window_->setView(player_camera);

		if (!(walk.getFlipped())) {
			flipped = true;
			walk.setFlipped(flipped);
		}

		current_animation = &walk;
		setTextureRect(current_animation->getCurrentFrame());

	}

	if (input->isKeyDown(sf::Keyboard::S))
	{
		//move player down
		move(0, (move_speed * frame_time_));

		//move the view
		player_camera.setCenter(this->getPosition());
		window_->setView(player_camera);

		current_animation = &walk;
		setTextureRect(current_animation->getCurrentFrame());
	}

	if (input->isKeyDown(sf::Keyboard::D))
	{
		//move right
		move((move_speed * frame_time_), 0);

		//move the view
		player_camera.setCenter(this->getPosition());
		window_->setView(player_camera);

		if (walk.getFlipped()) {
			flipped = false;
			walk.setFlipped(flipped);
		}

		current_animation = &walk;
		setTextureRect(current_animation->getCurrentFrame());
	}

	//if the player shoots
	if (input->isMouseLeftDown())
	{
		/*bulRequester->requestBullet(bulRequester->PLAYER, getPosition().x + 32, getPosition().y + 32, false);
		input->setMouseLeftDown(false);*/
	}
}

void Player::takeDamage(int amount_)
{
	health += amount_;
}
