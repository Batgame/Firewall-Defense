#include "Road.h"
#include <SFML/Graphics.hpp>


/*
Ajoute un chemin suivant à la Road
*/
void Road::addNextDirection(int direction)
{
	nextDirection[direction] = true;
}
/*
Soustrait un chemin suivant à la Road
*/
void Road::eraseNextDirection(int direction)
{
	nextDirection[direction] = false;
}

Road::Road(sf::Vector2f pos_, bool tab[4]) :pos(pos_)
{
}

int Road::getNextRoad(sf::Vector2f const& position)
{
	std::vector<int> directions;
	for (int i = 0; i < 4; i++)
	{
		if (nextDirection[i])
			directions.push_back(i);
	}
	//Retourne aléatoirement une des directions
	return directions[rand() % directions.size()];	
}

void Road::beDraw(sf::RenderWindow& rWindow)
{
	sf::RectangleShape r;
	r.setSize(sf::Vector2f(43, 43));
	r.setPosition(pos);
	r.setFillColor(sf::Color(200, 200, 200));
	rWindow.draw(r);
}
