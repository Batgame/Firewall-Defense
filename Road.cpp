#include <SFML/Graphics.hpp>
#include <iostream>
#include "header/Road.h"

/*
	Ajoute une ligne de chemin d'un point A -> B, ces points doivent être alligné sur X ou Y.
	à savoir 
*/


Road::Road(sf::Sprite spr_, sf::Vector2f pos_, std::vector<int> possiblePath) :pos(pos_), spr(spr_)
{
	spr.setScale(2.8125, 2.8125);
	nextDirection = possiblePath;
}

void Road::drawLine(std::vector<Road>& path ,sf::Vector2f a, sf::Vector2f b, sf::Sprite hor, sf::Sprite vert, sf::Sprite angle, sf::Sprite inter)
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
				path.push_back(Road(hor,sf::Vector2f(a.x + i, a.y), p));
			}
		}										
		else{							//SINON Chemin vers la gauche
			for (int i = 0; i + a.x >= b.x; i--)
			{
				std::vector<int> p;
				p.push_back(LEFT);			//Le chemin ne vas QUE vers la droite
				path.push_back(Road(hor,sf::Vector2f(a.x + i, a.y), p));
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
				path.push_back(Road(vert,sf::Vector2f(a.x, a.y + i), p));
			}
		}
		else {							//SINON Chemin vers le Haut
			for (int i = 0; i + a.y >= b.y; i--)
			{
				std::vector<int> p;
				p.push_back(UP);			//Le chemin ne vas que vers la haut
				path.push_back(Road(vert,sf::Vector2f(a.x, a.y + i), p));
			}
		}
	}
}

void Road::createMap(std::vector<Road>& map, int id, sf::Sprite hor, sf::Sprite vert, sf::Sprite angle, sf::Sprite inter)
{
	map.clear();


	hor.setOrigin(8, 8);
	vert.setOrigin(8, 8);
	angle.setOrigin(8, 8);
	inter.setOrigin(8, 8);

	switch (id)
	{
	case 1:// MAP 1
		//-----------------------------------TO DO--------------------------------
		Road::drawLine(map, sf::Vector2f(0, 6), sf::Vector2f(2, 6), hor, vert, angle, inter);
		Road::drawLine(map, sf::Vector2f(3, 6), sf::Vector2f(3, 5),hor, vert, angle, inter);//chemin du haut
		std::vector<int> p;
		p.push_back(DOWN);		
		map.push_back(Road(vert,sf::Vector2f(3, 7),p));
		Road::drawLine(map, sf::Vector2f(3, 8), sf::Vector2f(6, 8), hor, vert, angle, inter);
		Road::drawLine(map, sf::Vector2f(7, 8), sf::Vector2f(7, 7), hor, vert, angle, inter);
		Road::drawLine(map, sf::Vector2f(3, 4), sf::Vector2f(6, 4), hor, vert, angle, inter);
		Road::drawLine(map, sf::Vector2f(7, 4), sf::Vector2f(7, 5), hor, vert, angle, inter);
		Road::drawLine(map, sf::Vector2f(7, 6), sf::Vector2f(9, 6), hor, vert, angle, inter);
		Road::drawLine(map, sf::Vector2f(10, 6), sf::Vector2f(10, 8), hor, vert, angle, inter);
		Road::drawLine(map, sf::Vector2f(10, 9), sf::Vector2f(12, 9), hor, vert, angle, inter);
		Road::drawLine(map, sf::Vector2f(13, 9), sf::Vector2f(13, 3), hor, vert, angle, inter);
		Road::drawLine(map, sf::Vector2f(13, 2), sf::Vector2f(15, 2), hor, vert, angle, inter);
		Road::drawLine(map, sf::Vector2f(16, 2), sf::Vector2f(16, 6), hor, vert, angle, inter);
		Road::drawLine(map, sf::Vector2f(16, 7), sf::Vector2f(17, 7), hor, vert, angle, inter);
		Road::drawLine(map, sf::Vector2f(18, 7), sf::Vector2f(18, 12), hor, vert, angle, inter);
		Road::drawLine(map, sf::Vector2f(18, 13), sf::Vector2f(20, 13), hor, vert, angle, inter);
		Road::drawLine(map, sf::Vector2f(21, 13), sf::Vector2f(21, 8), hor, vert, angle, inter);
		Road::drawLine(map, sf::Vector2f(21, 7), sf::Vector2f(22, 7), hor, vert, angle, inter);
		Road::drawLine(map, sf::Vector2f(23, 7), sf::Vector2f(23, 6), hor, vert, angle, inter);//chemin du haut
		Road::drawLine(map, sf::Vector2f(23, 5), sf::Vector2f(24, 5), hor, vert, angle, inter);
		map.push_back(Road(vert, sf::Vector2f(23, 8), p));
		Road::drawLine(map, sf::Vector2f(23, 9), sf::Vector2f(24, 9), hor, vert, angle, inter);
		Road::drawLine(map, sf::Vector2f(25, 5), sf::Vector2f(25, 11), hor, vert, angle, inter);
		Road::drawLine(map, sf::Vector2f(25, 12), sf::Vector2f(28, 12), hor, vert, angle, inter);



		map[getId(map, sf::Vector2i(3, 6))].addNextDirection(DOWN);
		map[getId(map, sf::Vector2i(23, 7))].addNextDirection(DOWN);

		//---------------Inters---------------
		
		map[getId(map, sf::Vector2i(3, 6))].setSprite(inter);
		map[getId(map, sf::Vector2i(23, 7))].setSprite(inter);	
		map[getId(map, sf::Vector2i(25, 9))].setSprite(inter);
		//rotate a 180
		inter.rotate(180);
		map[getId(map, sf::Vector2i(7, 6))].setSprite(inter);

		


		//---------------Angles---------------
		//GAUCHE BAS
		map[getId(map, sf::Vector2i(10, 6))].setSprite(angle);
		map[getId(map, sf::Vector2i(16, 2))].setSprite(angle);
		map[getId(map, sf::Vector2i(7, 4))].setSprite(angle);	
		map[getId(map, sf::Vector2i(18, 7))].setSprite(angle);	
		map[getId(map, sf::Vector2i(25, 5))].setSprite(angle);


		angle.rotate(90);

		//GAUCHE HAUT		
		map[getId(map, sf::Vector2i(13, 9))].setSprite(angle);
		map[getId(map, sf::Vector2i(7, 8))].setSprite(angle);	
		map[getId(map, sf::Vector2i(21, 13))].setSprite(angle);	

		angle.rotate(90);

		//DROITE HAUT 
		map[getId(map, sf::Vector2i(3, 8))].setSprite(angle);	
		map[getId(map, sf::Vector2i(16, 7))].setSprite(angle);		
		map[getId(map, sf::Vector2i(18, 13))].setSprite(angle);	
		map[getId(map, sf::Vector2i(23, 9))].setSprite(angle);
		map[getId(map, sf::Vector2i(25, 12))].setSprite(angle);
		map[getId(map, sf::Vector2i(10, 9))].setSprite(angle);	


		angle.rotate(90);
		//DROITE BAS
		map[getId(map, sf::Vector2i(3, 4))].setSprite(angle);
		map[getId(map, sf::Vector2i(13, 2))].setSprite(angle);	
		map[getId(map, sf::Vector2i(21, 7))].setSprite(angle);	
		map[getId(map, sf::Vector2i(23, 5))].setSprite(angle);
	



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

void Road::setSprite(sf::Sprite spr_)
{
	spr = spr_;
}

sf::Vector2f Road::getPos() const
{
	return pos;
}



int Road::getNextRoad() const
{
	//Retourne aléatoirement une des directions
	return nextDirection[rand() % nextDirection.size()];
}

std::vector<int> Road::getNextRoadTab() const
{
	return nextDirection;
}

void Road::beDraw(sf::RenderWindow& rWindow)
{
	spr.setPosition(sf::Vector2f((pos.x + 0.5) * 45,(pos.y + 0.5) * 45));
	sf::Sprite newSpr = spr;
	rWindow.draw(newSpr);
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
	return -1;//Crash volontairement le jeux
}

int Road::getNextdirectionNb()
{
	return nextDirection.size();
}
