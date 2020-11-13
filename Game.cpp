#include "Game.h"
#include "Road.h"
#include "Turret.h"
#include <iostream>
#include <math.h>

float getDistance(sf::Vector2f a, sf::Vector2f b);

Game::Game(int map_) : map(map_),money(500)
{
	Road::createMap(roads,map);

	for (int i = 0; i < 8; ++i)
	{
		trojans.push_back(Trojan(sf::Vector2f(0.5, 4.5), RIGHT,20));
	}

	switch (map)
	{
	case 1:
		turrets.push_back(Turret(sf::Vector2i(7, 6), AVAST));
		turrets.push_back(Turret(sf::Vector2i(13,4), KASPERSKY));
		break;
	case 2:




		break;
	case 3:




		break;

	}
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

	//--------MORTAR----------
	for (int i = 0; i < mortars.size(); ++i)
	{
		mortars[i].refresh(dt);
		if (!mortars[i].isAlive())
		{
			sf::Vector2f explosion = mortars[i].getPos();
			int damage = mortars[i].getDamage();
			float radius = mortars[i].getRadius();

			for (int j = 0; j < trojans.size(); ++j)
			{
				if (getDistance(explosion, trojans[j].getPos()) < radius)
				{
					trojans[j].hit(damage);
				}
			}
			mortars.erase(mortars.begin() + i);
			--i;
		}
	}

	//Kill

	for (int i = 0; i < projectiles.size(); ++i)
	{
		if (!projectiles[i].isAlive() || projectiles[i].getPos().x < 0 || projectiles[i].getPos().y > 40 || projectiles[i].getPos().y < 0 || projectiles[i].getPos().y > 40)
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
			money += 20;
		}
	}
	refreshTurrets(dt);

}

void Game::refreshTurrets(sf::Time const& dt)
{
	for (int i = 0; i < turrets.size(); i++)
	{
		turrets[i].resfresh(dt);
		if (turrets[i].canShoot())
		{
			sf::Vector2f aim = sf::Vector2f(-1000, -1000);	//Quelle est le Trojan le plus proche ?
			for (int j = 0; j < trojans.size() && turrets[i].canShoot(); j++)
			{
				sf::Vector2f centerPos = turrets[i].getPos();
				centerPos.x += 0.5;
				centerPos.y += 0.5;
				if (getDistance(trojans[j].getPos(),centerPos) < turrets[i].getRange())
				{
					if (turrets[i].id == KASPERSKY)
					{
						mortars.push_back(turrets[i].createMortar(trojans[j].getFuturePos()));
					}
					else
					{
						projectiles.push_back(turrets[i].createProjectile());
					}
				}
			}
		}
	}

}

void Game::beDraw(sf::RenderWindow& rWindow) const
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
	for (int i = 0; i < mortars.size(); i++)
	{
		mortars[i].beDraw(rWindow);
	}
}

float getDistance(sf::Vector2f a, sf::Vector2f b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}