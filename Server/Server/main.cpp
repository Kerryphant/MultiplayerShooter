#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "Server.h"



int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	Server server;

	while (window.isOpen())
	{
		server.update(&window);
	}

	return 0;
}