#include "..\include\TileMap.h"
#include <iostream>

TileMap::TileMap()
{
	//setting up the coords for inividual tiles
	tiles.push_back(sf::IntRect(0, 0, 64, 64));
	tiles.push_back(sf::IntRect(66, 0, 64, 64));
	tiles.push_back(sf::IntRect(0, 66, 64, 64));
	tiles.push_back(sf::IntRect(66, 66, 64, 64));
	tiles.push_back(sf::IntRect(0, 131, 64, 64));
	tiles.push_back(sf::IntRect(64, 131, -64, 64));
}

TileMap::~TileMap()
{
	for (Tile* i : tileMap) {
		delete i;
	}
}


void TileMap::setWindow(sf::RenderWindow * hwnd_)
{
	window = hwnd_;
}

void TileMap::loadMapFile(std::string path_)
{

	// open file
	std::ifstream inputFile(path_);

	std::cout << "attempting to load from file" << std::endl;

	// test file open
	if (inputFile) {
		std::cout << "file is open" << std::endl;
		int value = 0;

		// read the elements in the file into a vector
		while (inputFile >> value) {
			rawMap.push_back(value);
			//std::cout << value << std::endl;
		}

		// close the file
		inputFile.close();
	}
	else {
		std::cout << "failed to open file" << std::endl;
	}
}

void TileMap::setMap()
{
	//w = 7
	//h = 4
	int counter = 0;
	int previousTile = 9;

	for (int row = 0; row < 15; row++) {
		for (int col = 0; col < 17; col++) {
			Tile* tempTile = new Tile();

			tempTile->setPosition((float)(col * 64), (float)(row * 64));
			tempTile->setTileTexture(tiles[rawMap[counter]]);
			tempTile->setCollisionBox(tempTile->getPosition().x, tempTile->getPosition().y, 64, 64);
			
			if (rawMap[counter] == 4 || rawMap[counter] == 2 || rawMap[counter] == 3) 
			{
				tempTile->setIsWall(true);
			}

			//if this is the first tile, or this is wall tile when the previous tile was also a wall tile
			if (previousTile == 9 || previousTile == 4 && rawMap[counter] == 4) 
			{
				//flip the wall tile
				tempTile->setTileTexture(tiles[5]);
				tempTile->setTileType(Tile::LEFT);
			}
			else if (rawMap[counter] == 4) 
			{
				tempTile->setTileType(Tile::RIGHT);
			}

			if ((rawMap[counter] == 2 || rawMap[counter] == 3) && tempTile->getPosition().y == 0)
			{
				tempTile->setTileType(Tile::TOP);
			}
			else if ((rawMap[counter] == 2 || rawMap[counter] == 3) && tempTile->getPosition().y > 0)
			{
				tempTile->setTileType(Tile::BOTTOM);
			}

			tileMap.push_back(tempTile);
			
			previousTile = rawMap[counter];
			counter++;	
		}
	}
}

void TileMap::drawMap()
{
	for (Tile* i : tileMap) {
		window->draw(*i);
	}
}

std::vector<Tile*> TileMap::getTileMap()
{
	return tileMap;
}

