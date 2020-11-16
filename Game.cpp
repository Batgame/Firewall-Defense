#include "Game.h"
#include "Road.h"
#include "Turret.h"
#include <iostream>
#include <math.h>
#include <SFML/System.hpp>

float getDistance(sf::Vector2f a, sf::Vector2f b);

Game::Game(int map_) : map(map_), money(500), level(0),trojanCount(0),sprsAvast(Spritesheet("addons/Avast.png",11,1)),sprsKaspersky(Spritesheet("addons/Kaspersky.png",9,1)),delayWave(DELAY_WAVE)
, sprsUSBKillers(Spritesheet("addons/usb_killer.png", 4, 1)),sprsTrojan(Spritesheet("addons/Trojan.png",5,1))
{
	bg.loadFromFile("addons/ingameBackground.jpg");
	sprBg = sf::Sprite(bg);
	selectedTurret = AVAST;

	Road::createMap(roads,map);
	levelUp();

	switch (map)
	{
	case 1:

		break;
	case 2:




		break;
	case 3:

		break;
	}
}

void Game::refresh(sf::Time& dt)
{

	//----------------SHOP-------------
	
	


	//---------------------SPEED UP-----------------

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{ 
		dt *= 5.f;
	}

	//-------------SPAWN PART ---------------------
	delaySpawn -= dt.asSeconds();
	if (delaySpawn < 0) delaySpawn = 0;

	if (delaySpawn == 0)
	{
		if (usbKillerCount > 0)
		{
			usbKillerCount--;
			delaySpawn = DELAY_SPAWN;
			switch (map)
			{
				case 1: 
					usbKillers.push_back(USBKiller(&sprsUSBKillers,sf::Vector2f(0.5,6.5),1));
					break;
			}
		}
		else if (trojanCount > 0)
		{
			trojanCount--;
			delaySpawn = DELAY_SPAWN;
			switch (map)
			{
			case 1:
				trojans.push_back(Trojan(&sprsTrojan,sf::Vector2f(0.5, 6.5), 1));
				break;
			}
		}
	}



	for (int i = 0; i < trojans.size(); ++i)
	{
		trojans[i].refresh(dt,roads);
	}
	for (int i = 0; i < usbKillers.size(); ++i)
	{
		usbKillers[i].refresh(dt, roads);
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
		for (int j = 0; j < usbKillers.size(); ++j)
		{
			if (getDistance(usbKillers[j].getPos(), projectiles[i].getPos()) < getDistance(aim, projectiles[i].getPos()))
			{
				aim = usbKillers[j].getPos();
			}
		}
		projectiles[i].refresh(dt,aim);
	}

	//test des dégats et des 

	for (int i = 0; i < projectiles.size(); ++i)
	{
		if (projectiles[i].isAlive())
		{
			for (int j = 0; j < trojans.size(); ++j)
			{
				if (projectiles[i].isAlive() && getDistance(trojans[j].getPos(), projectiles[i].getPos()) < 0.5)
				{
					trojans[j].hit(projectiles[i].getDamage());
					projectiles[i].kill();
				}
			}
			for (int j = 0; j < usbKillers.size(); ++j)
			{
				if (projectiles[i].isAlive() && getDistance(usbKillers[j].getPos(), projectiles[i].getPos()) < 0.5)
				{
					usbKillers[j].hit(projectiles[i].getDamage());
					projectiles[i].kill();
				}
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
			for (int j = 0; j < usbKillers.size(); ++j)
			{
				if (getDistance(explosion, usbKillers[j].getPos()) < radius)
				{
					usbKillers[j].hit(damage);
				}
			}
			mortars.erase(mortars.begin() + i);
			--i;
		}
	}

	//Kill
	if (trojans.size() == 0 && usbKillers.size() == 0) {projectiles.clear();}

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
			money += TROJAN_VALUE;
		}
	}

	for (int i = 0; i < usbKillers.size(); ++i)
	{
		if (!usbKillers[i].isAlive())
		{
			usbKillers.erase(usbKillers.begin() + i);
			--i;
			money += USBKILLER_VALUE;
		}
	}

	refreshTurrets(dt);

	//---------------------------------WAVE CLEAR-------------------------------
	if(trojans.size() == 0 && usbKillers.size() == 0)
	{
		delayWave -= dt.asSeconds();
		if (delayWave < 0)
		{
			levelUp();
			delayWave = DELAY_WAVE;
		}
	}

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

			for (int j = 0; j < usbKillers.size() && turrets[i].canShoot(); j++)
			{
				sf::Vector2f centerPos = turrets[i].getPos();
				centerPos.x += 0.5;
				centerPos.y += 0.5;
				if (getDistance(usbKillers[j].getPos(), centerPos) < turrets[i].getRange())
				{
					if (turrets[i].id == KASPERSKY)
					{
						mortars.push_back(turrets[i].createMortar(usbKillers[j].getFuturePos()));
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

void Game::setSelectedTurret(int const& turret)
{
	selectedTurret = turret;
}

void Game::buyTurret(int& mouseX, int& mouseY,sf::RenderWindow& rWindow, sf::View view)
{	
	int posX = int(rWindow.mapPixelToCoords(sf::Mouse::getPosition(rWindow), view).x / 45);
	int posY = int(rWindow.mapPixelToCoords(sf::Mouse::getPosition(rWindow), view).y / 45);

	if (Road::getId(roads, sf::Vector2i(posX, posY)) == -1)
	{
		switch (selectedTurret)
		{
		case AVAST:
			if (money >= AVAST_PRICE)
			{
				money -= AVAST_PRICE;
				bool validPlace = true;
				for (int i = 0; i < turrets.size(); ++i)
				{
					if (turrets[i].getPos() == sf::Vector2f(posX, posY))
					{
						i = turrets.size();
						validPlace = false;
					}
				}
				if(validPlace)
				turrets.push_back(Turret(sf::Vector2i(posX, posY), &sprsAvast, AVAST));

			}
			break;
		case KASPERSKY:
			if (money >= KASPERSKY_PRICE)
				turrets.push_back(Turret(sf::Vector2i(posX, posY),&sprsKaspersky, KASPERSKY));
			break;
		}
	}
}

void Game::sellTurret(int& mouseX, int& mouseY, sf::RenderWindow& rWindow, sf::View view)
{
	int posX = int(rWindow.mapPixelToCoords(sf::Mouse::getPosition(rWindow), view).x / 45);
	int posY = int(rWindow.mapPixelToCoords(sf::Mouse::getPosition(rWindow), view).y / 45);

	bool validPlace = false;
	for (int i = 0; i < turrets.size(); ++i)
	{
		if (turrets[i].getPos() == sf::Vector2f(posX, posY))
		{
			switch (turrets[i].id)
			{
			case AVAST:
				money += AVAST_PRICE/2;
				break;
			case KASPERSKY:
				money += KASPERSKY_PRICE / 2;
				break;
			}
			turrets.erase(turrets.begin() + i);
			i = turrets.size();
		}
	}

}

void Game::levelUp()
{
	level++;

	if (level % 7 == 0)
	{
		//BOSS SPAWN !
	}
	else
	{
		switch (level % 3)
		{
		case 1:
			usbKillerCount = 5;
			break;
		case 2:
			usbKillerCount = 10;
			break;
		}

		switch (int(level / 2) % 3)
		{
		case 0:
			break;
		case 1:
			trojanCount = 2;
			break;
		case 2:
			trojanCount = 4;
			break;

		}

	}


	/*
	usbKillerCount = 0.4f * level * level + 5;
	if (level > 3)
	{
		trojanCount = 0.2f * (level-3) * (level-3) + 5;
	}*/
}

void Game::beDraw(sf::RenderWindow& rWindow, sf::View const& view) 
{
	sprBg.setScale(view.getSize().x / bg.getSize().x, view.getSize().y / bg.getSize().y);
	sprBg.setPosition(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2);
	rWindow.draw(sprBg);


	for (int i = 0; i < roads.size(); i++)
	{
		roads[i].beDraw(rWindow);
	}
	for (int i = 0; i < trojans.size(); i++)
	{
		trojans[i].beDraw(rWindow);
	}
	for (int i = 0; i < usbKillers.size(); i++)
	{
		usbKillers[i].beDraw(rWindow);
	}
	for (int i = 0; i < projectiles.size(); i++)
	{
		projectiles[i].beDraw(rWindow);
	}
	for (int i = 0; i < mortars.size(); i++)
	{
		mortars[i].beDraw(rWindow);
	}
	for (int i = 0; i < turrets.size(); i++)
	{
		turrets[i].beDraw(rWindow);
	}
}

float getDistance(sf::Vector2f a, sf::Vector2f b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}