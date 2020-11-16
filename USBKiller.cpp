#include "USBKiller.h"
#include "Road.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Spritesheet.h"
#include "Animation.h" 

USBKiller::USBKiller(Spritesheet* sprs,sf::Vector2f pos_, int direction) :pos(pos_), hp(HP), distanceToWalk(0), speed(SPEED_MAX),anim(Animation(sprs,0.5,1,1))
{
	speed = SPEED_MAX;
}

void USBKiller::refresh(sf::Time const& dt, std::vector<Road>& roads)
{
	anim.refresh(dt);
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

		//-------Centrage du USBKiller sur la tuile actuelle-----

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

void USBKiller::beDraw(sf::RenderWindow& rWindow) const
{
	sf::Sprite spr = anim.getSprite();
	spr.setScale(2,2);
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
		spr.setRotation(180);
		break;
	}

	spr.setPosition(pos.x * 45 , pos.y * 45);

	rWindow.draw(spr);
}

void USBKiller::hit(int damage)
{
	hp -= damage;
	if (hp < 0)hp = 0;
}

bool USBKiller::isAlive()
{
	return hp > 0;
}

sf::Vector2f USBKiller::getPos()
{
	return pos;
}

sf::Vector2f USBKiller::getFuturePos()
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
