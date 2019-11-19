#pragma once
#include "SFML\Graphics.hpp"
#include <vector>

class Animation
{
public:
	Animation();
	~Animation();

	// Create animation
	void addFrame(sf::IntRect rect_);
	void setFrameSpeed(float speed_);
	int getSize();

	// update/reset animation
	void animate(float frame_time_);
	void reset();

	// get current frame of animation
	sf::IntRect getCurrentFrame();

	// Animation controls
	float getFrameSpeed() { return animationSpeed; };

	void setFlipped(bool flip_) { flipped = flip_; };
	bool getFlipped() {	return flipped;	};

	void setLooping(bool loop_) { isLooping = loop_; };
	bool getLooping() { return isLooping; };

	void setPlaying(bool play_) { isPlaying = play_; };
	bool getPlaying() { return isPlaying; };

protected:
	std::vector<sf::IntRect>frames;
	sf::IntRect frame;
	int currentFrame;
	float animationSpeed;	// in FPS
	bool flipped;
	bool isLooping;
	bool isPlaying;
	float elapsedTime;
};