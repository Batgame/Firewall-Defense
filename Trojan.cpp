#include "Trojan.h"
#include "Road.h"
#include <SFML/Graphics.hpp>

Trojan::Trojan(sf::Vector2f pos_, int direction, int hp_):pos(pos_),hp(hp_),distanceToWalk(1),speed(SPEED_MAX)
{
	speed = (rand() % int(SPEED_MAX/2 * 100)) / 100.f + SPEED_MAX/2;
}

void Trojan::refresh(sf::Time const& dt, std::vector<Road>& roads)
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

		int idRoad = Road::getId(roads, sf::Vector2i(pos.x, pos.y));

		if (idRoad >= 0 && idRoad < roads.size())
		{
			direction = roads[idRoad].getNextRoad();
			pos.x = int(roads[idRoad].getPos().x) + 0.5;
			pos.y = int(roads[idRoad].getPos().y) + 0.5;
		}
		else
		{
			hp = 0;
		}
	}
}

void Trojan::beDraw(sf::RenderWindow& rWindow) const
{
	sf::CircleShape c;
	c.setRadius(15);
	c.setFillColor(sf::Color(140,140,140));
	c.setPosition(pos.x * 45 - 15, pos.y * 45 - 15);
	rWindow.draw(c);
}

void Trojan::hit(int damage)
{
	hp -= damage;
	if (hp < 0)hp = 0;
}

bool Trojan::isAlive()
{
	return hp > 0;
}

sf::Vector2f Trojan::getPos()
{
	return pos;
}

sf::Vector2f Trojan::getFuturePos()
{
	sf::Vector2f v = sf::Vector2f(pos.x, pos.y);
	switch (direction)
	{
	case UP:
		v.y -= speed;
		break;
	case RIGHT:
		v.x += speed;
		break;
	case DOWN:
		v.y += speed;
		break;
	case LEFT:
		v.x -= speed;
		break;
	}
	return v;
}
