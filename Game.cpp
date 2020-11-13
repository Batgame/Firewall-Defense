#include "Game.h"
#include "Road.h"
#include <iostream>
#include <math.h>

float getDistance(sf::Vector2f a, sf::Vector2f b);

Game::Game(int map_) : map(map_)
{
	Road::createMap(roads,map);

	for (int i = 0; i < 8; ++i)
	{
		trojans.push_back(Trojan(sf::Vector2f(0.5, 4.5), RIGHT,20));
	}
	for (int i = 0; i < 10; ++i)
	{
		projectiles.push_back(Projectile(sf::Vector2f(rand()%10 + 10, rand()%10 + 10),MISSILE,8));
	}

	for (int i = 0; i < 30; ++i)
		std::cout << roads[0].getNextRoad() << std::endl;
}

void Game::refresh(sf::Time const& dt)
{
	for (int i = 0; i < trojans.size(); ++i)
	{
		trojans[i].refresh(dt,roads);
	}

	for (int i = 0; i < projectiles.size(); ++i)
	{
		sf::Vector2f aim = sf::Vector2f(-1000,-1000);	//Quelle est le Trojan le plus proche ?
		for (int j = 0; j < trojans.size(); ++j)
		{
			if (getDistance(trojans[j].getPos(),projectiles[i].getPos()) < getDistance(aim, projectiles[i].getPos()))
			{
				aim = trojans[j].getPos();
			}
		}
		projectiles[i].refresh(dt,aim);
	}

	//test des dégats et des 

	for (int i = 0; i < projectiles.size(); ++i)
	{
		for (int j = 0; j < trojans.size(); ++j)
		{
			if (projectiles[i].isAlive() && getDistance(trojans[j].getPos(), projectiles[i].getPos()) < 0.5)
			{
				trojans[j].hit(projectiles[i].getDamage());
				projectiles[i].kill();
			}
		}
	}

	//Kill

	for (int i = 0; i < projectiles.size(); ++i)
	{
		if (!projectiles[i].isAlive())
		{
			projectiles.erase(projectiles.begin() + i);
			--i;
		}
	}

	for (int i = 0; i < trojans.size(); ++i)
	{
		if (!trojans[i].isAlive())
		{
			trojans.erase(trojans.begin() + i);
			--i;
		}
	}

}

void Game::beDraw(sf::RenderWindow& rWindow)
{
	for (int i = 0; i < roads.size(); i++)
	{
		roads[i].beDraw(rWindow);
	}
	for (int i = 0; i < trojans.size(); i++)
	{
		trojans[i].beDraw(rWindow);
	}

	for (int i = 0; i < projectiles.size(); i++)
	{
		projectiles[i].beDraw(rWindow);
	}
}

float getDistance(sf::Vector2f a, sf::Vector2f b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}