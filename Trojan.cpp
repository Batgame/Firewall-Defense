#include "Trojan.h"
#include "header/Road.h"
#include <SFML/Graphics.hpp>

Trojan::Trojan(sf::Vector2f pos_, int direction, int hp_):pos(pos_),hp(hp_),distanceToWalk(1),speed(SPEED_MAX)
{
	speed = (rand() % (SPEED_MAX/2 * 100)) / 100.f + SPEED_MAX/2;
}

void Trojan::refresh(sf::Time const& dt, std::vector<Road> const& roads)
{
	distanceToWalk -= speed * dt.asSeconds();

	switch (direction)
	{
	case 0:
		pos.y -= speed * dt.asSeconds();
		break;
	case 1:
		pos.x += speed * dt.asSeconds();
		break;
	case 2:
		pos.y += speed * dt.asSeconds();
		break;
	case 3:
		pos.x -= speed * dt.asSeconds();
		break;
	}

	if (distanceToWalk < 0)
	{
		distanceToWalk = 1;

		//-------Centrage du Trojan sur la tuile actuelle-----


		for (int i = 0; i < roads.size(); i++)
		{
			if (roads[i].getPos().x == int(pos.x) && roads[i].getPos().y == int(pos.y))
			{
				direction = roads[i].getNextRoad();

				pos.x = int(roads[i].getPos().x) + 0.5;
				pos.y = int(roads[i].getPos().y) + 0.5;
			}
		}
	}
}

void Trojan::beDraw(sf::RenderWindow& rWindow)
{
	sf::CircleShape c;
	c.setRadius(15);
	c.setFillColor(sf::Color(140,140,140));
	c.setPosition(pos.x * 45 - 15, pos.y * 45 - 15);
	rWindow.draw(c);
}

