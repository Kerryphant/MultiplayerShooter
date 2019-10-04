#include "..\include\Tile.h"

Tile::Tile() : isWall(false), type(CENTRE)
{
	texture.loadFromFile("Media/Sprites/Tiles/DungeonTileSet.png");

	setTexture(&texture);

	setSize(sf::Vector2f(64, 64));
}

Tile::~Tile()
{

}

void Tile::setTileTexture(sf::IntRect rect)
{
	setTextureRect(rect);
}

void Tile::setIsWall(bool isWall_)
{
	isWall = isWall_;
}

bool Tile::getIsWall()
{
	return isWall;
}

