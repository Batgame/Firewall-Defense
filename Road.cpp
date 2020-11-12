#include "Road.h"
#include <SFML/Graphics.hpp>
#include <iostream>

void Road::drawLine(std::vector<Road>& path ,sf::Vector2f a, sf::Vector2f b)
{
	//HorizontalLine
	if (a.y == b.y)
	{
		if (b.x > a.x)					//Chemin vers la DROITE ! Car B.X > A.X
		{
			for (int i = 0; i + a.x <= b.x; i++)
			{
				std::vector<int> p;
				p.push_back(RIGHT);			//Le chemin ne vas QUE vers la droite
				path.push_back(Road(sf::Vector2f(a.x + i, a.y), p));
			}
		}										
		else{							//SINON Chemin vers la gauche
			for (int i = 0; i + a.x >= b.x; i--)
			{
				std::vector<int> p;
				p.push_back(LEFT);			//Le chemin ne vas QUE vers la droite
				path.push_back(Road(sf::Vector2f(a.x + i, a.y), p));
			}
		}
	}
	else//VerticalLine
	{
		if (b.y > a.y)					//Chemin vers le BAS ! Car B.Y > A.Y
		{
			for (int i = 0; i + a.y <= b.y; i++)
			{
				std::vector<int> p;
				p.push_back(DOWN);			//Le chemin ne vas QUE vers le bas
				path.push_back(Road(sf::Vector2f(a.x, a.y + i), p));
			}
		}
		else {							//SINON Chemin vers le Haut
			for (int i = 0; i + a.y >= b.y; i--)
			{
				std::vector<int> p;
				p.push_back(UP);			//Le chemin ne vas que vers la haut
				path.push_back(Road(sf::Vector2f(a.x, a.y + i), p));
			}
		}
	}
}

void Road::createMap(std::vector<Road>& map, int id)
{
	map.clear();

	switch (id)
	{
	case 1:// MAP 1
		//-----------------------------------TO DO--------------------------------
		//Ligne simple de gauche à droite 
		std::cout << "CONTRUCTION D'UNE MAP DE 1ER NIVEAU" << std::endl;
		Road::drawLine(map, sf::Vector2f(0, 4), sf::Vector2f(3, 4));
		Road::drawLine(map, sf::Vector2f(4, 4), sf::Vector2f(4, 11));
		Road::drawLine(map, sf::Vector2f(4, 12), sf::Vector2f(2, 12));
		Road::drawLine(map, sf::Vector2f(1, 12), sf::Vector2f(1, 13));
		Road::drawLine(map, sf::Vector2f(1, 14), sf::Vector2f(8, 14));
		Road::drawLine(map, sf::Vector2f(9, 14), sf::Vector2f(9, 8));
		Road::drawLine(map, sf::Vector2f(9, 7), sf::Vector2f(7, 7));
		Road::drawLine(map, sf::Vector2f(6, 7), sf::Vector2f(6, 6));

		break;
	}
}

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

Road::Road(sf::Vector2f pos_, std::vector<int> possiblePath) :pos(pos_)
{
	nextDirection = possiblePath;
}

int Road::getNextRoad(sf::Vector2f const& position)
{
	//Retourne aléatoirement une des directions
	return nextDirection[rand() % nextDirection.size()];
}

void Road::beDraw(sf::RenderWindow& rWindow)
{
	sf::RectangleShape r;
	r.setSize(sf::Vector2f(43, 43));
	r.setPosition(pos.x * 45, pos.y * 45);
	rWindow.draw(r);
	
	switch (nextDirection[0])
	{
	case 0:
		r.setFillColor(sf::Color::Red);	//UP

		break;
	case 1:
		r.setFillColor(sf::Color::Green);	//DROITE

		break;
	case 2:
		r.setFillColor(sf::Color::Yellow);	//BAS

		break;
	case 3:
		r.setFillColor(sf::Color::Blue);	//LEFT

		break;
	}
}
