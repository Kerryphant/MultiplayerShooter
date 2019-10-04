#pragma once
#include "..\include\Sprite.h"

class Tile : public Sprite {

public:

	Tile();
	~Tile();

	enum tileType { TOP, BOTTOM, LEFT, RIGHT, CENTRE};
	
	void setTileTexture(sf::IntRect rect);
	void setIsWall(bool isWall_);
	bool getIsWall();
	void setTileType(tileType type_) { type = type_; }
	tileType getTileType() { return type; }

private:
	
	bool isWall;
	tileType type;

};