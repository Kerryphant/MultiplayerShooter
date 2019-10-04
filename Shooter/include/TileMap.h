#pragma once
#include <vector>
#include <fstream>
#include "..\include\Tile.h"


class TileMap {

public:

	TileMap();
	~TileMap();

	//Populates tileMap vector according to rawMap data
	void setWindow(sf::RenderWindow* hwnd_);
	void loadMapFile(std::string path_);
	void setMap();
	void drawMap();
	std::vector<Tile*> getTileMap();
	

private:

	std::vector<sf::IntRect> tiles; //used by tiles to set their texture
	std::vector<int> rawMap; //stores integer values to tell the program which tile to draw
	std::vector<Tile*> tileMap; //pointers to tiles which have their textures

	sf::RenderWindow* window;
};