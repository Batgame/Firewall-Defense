#include <SFML/Graphics.hpp>
#include <iostream>
#include "Road.h"

/*
	Ajoute une ligne de chemin d'un point A -> B, ces points doivent être alligné sur X ou Y.
	à savoir 
*/

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
		Road::drawLine(map, sf::Vector2f(0, 4), sf::Vector2f(3, 4));
		Road::drawLine(map, sf::Vector2f(4, 4), sf::Vector2f(4, 11));
		Road::drawLine(map, sf::Vector2f(4, 12), sf::Vector2f(2, 12));
		Road::drawLine(map, sf::Vector2f(1, 12), sf::Vector2f(1, 13));
		Road::drawLine(map, sf::Vector2f(1, 14), sf::Vector2f(8, 14));
		Road::drawLine(map, sf::Vector2f(9, 14), sf::Vector2f(9, 8));
		Road::drawLine(map, sf::Vector2f(9, 7), sf::Vector2f(7, 7));
		Road::drawLine(map, sf::Vector2f(6, 7), sf::Vector2f(6, 6));
		Road::drawLine(map, sf::Vector2f(6, 5), sf::Vector2f(11, 5));
		Road::drawLine(map, sf::Vector2f(12, 5), sf::Vector2f(12, 4));
		Road::drawLine(map, sf::Vector2f(14, 3), sf::Vector2f(14, 10));
		Road::drawLine(map, sf::Vector2f(14, 11), sf::Vector2f(19, 11));

		//----RACCOURCI----
		Road::drawLine(map, sf::Vector2f(4,3), sf::Vector2f(13, 3));
		//----INTERSECTION
		map[getId(map,sf::Vector2i(4,4))].addNextDirection(UP);
		break;
	}
}

/*
Ajoute un chemin suivant à la Road
*/
void Road::addNextDirection(int const& direction)
{
	bool doublon = false;
	for (int i = 0; i < nextDirection.size() && !doublon; i++)	//Vérification anti-doublon
	{
		if (nextDirection[i] == direction)
			doublon = true;
	}

	if (!doublon)
	{
		nextDirection.push_back(direction);
	}
}
/*
Soustrait un chemin suivant à la Road
*/
void Road::eraseNextDirection(int const& direction)
{
	int idDirection = -1;
	for (int i = 0; i < nextDirection.size(); i++)	//Vérification anti-doublon
	{
		if (nextDirection[i] == direction)
			idDirection = i;
	}

	if (idDirection >= 0)
	{
		nextDirection.erase(nextDirection.begin() + idDirection);
	}
}

sf::Vector2f Road::getPos() const
{
	return pos;
}

Road::Road(sf::Vector2f pos_, std::vector<int> possiblePath) :pos(pos_)
{
	nextDirection = possiblePath;
}


int Road::getNextRoad() const
{
	//Retourne aléatoirement une des directions
	return nextDirection[rand() % nextDirection.size()];
}

void Road::beDraw(sf::RenderWindow& rWindow) const
{
	sf::RectangleShape r;
	r.setSize(sf::Vector2f(43, 43));
	r.setPosition(pos.x * 45, pos.y * 45);
	r.setFillColor(sf::Color(0, 113, 202));

	rWindow.draw(r);

}

/*
	Permet d'obtenir la case du tableau vector<Road> correspondant à une position
*/

int Road::getId(std::vector<Road>& map, sf::Vector2i const& pos_)
{
	for (int i = 0; i < map.size(); i++)
	{
		if (int(map[i].getPos().x) == int(pos_.x) && int(map[i].getPos().y == pos_.y))
			return i;
	}
	
	std::cout << "pos_ : "<<pos_.x <<" : "<<pos_.y << std::endl;

	return -1;//Crash volontairement le jeux
}
