#include "header/Trojan.h"
#include "header/Road.h"
#include <SFML/Graphics.hpp>
#include "header/Spritesheet.h"
#include "header/Animation.h"

Trojan::Trojan(Spritesheet *sprs,sf::Vector2f pos_, int direction_, int hp_):pos(pos_),hp(hp_),distanceToWalk(0),speed(SPEED_MAX),anim(Animation(sprs,0.7)),direction(direction_)
{
	speed = SPEED_MAX;
}

void Trojan::refresh(sf::Time const& dt, std::vector<Road>& roads)
{
	distanceToWalk -= speed * dt.asSeconds();
	anim.refresh(dt);
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
			pos.x = int(roads[idRoad].getPos().x) + 0.5001;
			pos.y = int(roads[idRoad].getPos().y) + 0.5001;
		}
		else
		{
			hp = 0;
		}
	}
}

void Trojan::beDraw(sf::RenderWindow& rWindow) const
{
	sf::Sprite spr = anim.getSprite();
	spr.setScale(3, 3);
	spr.setOrigin(8, 8);

	switch (direction)
	{
	case UP:
		spr.setRotation(-90);
		break;
	case DOWN:
		spr.setRotation(90);
		break;
	case LEFT:
		spr.setScale(-2,2);
		break;
	}

	spr.setPosition(pos.x * 45, pos.y * 45);

	sf::RectangleShape r(sf::Vector2f(hp * 2,6));
	r.setOrigin(hp, 1.5);
	r.setPosition(pos.x * 45, (pos.y - 0.7) * 45);
	r.setFillColor(sf::Color::Red);

	rWindow.draw(spr);
	rWindow.draw(r);

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
