#include "header/Game.h"
#include "header/Road.h"
#include "header/Turret.h"
#include <iostream>
#include <math.h>
#include <string>
#include "header/TextureManager.h"
#include <SFML/System.hpp>
#include "header/Shop.h"

float getDistance(sf::Vector2f a, sf::Vector2f b);

extern sf::Font font;

Game::Game(int map_) : map(map_), money(500), level(0),trojanCount(0),hp(100),sprsAvast(Spritesheet("addons/Avast.png",11,1)),sprsKaspersky(Spritesheet("addons/Kaspersky.png",9,1)),delayWave(DELAY_WAVE)
, sprsUSBKillers(Spritesheet("addons/usb_killer.png", 4, 1)),sprsTrojan(Spritesheet("addons/Trojan.png",5,1))
{
	sizeX = 28;
	sizeY = 16;
	textureBg0.loadFromFile("addons/bg0.png");
	textureBg1.loadFromFile("addons/bg1.png");
	textureBg2.loadFromFile("addons/bg2.png");
	textureBg3.loadFromFile("addons/bg3.png");

	sprBg0 = sf::Sprite(textureBg0);
	sprBg1 = sf::Sprite(textureBg1);
	sprBg2 = sf::Sprite(textureBg2);
	sprBg3 = sf::Sprite(textureBg3);

	sprBg0.setScale(2.8125, 2.8125);
	sprBg1.setScale(2.8125, 2.8125);
	sprBg2.setScale(2.8125, 2.8125);
	sprBg3.setScale(2.8125, 2.8125);

	textureRoadHorizontal.loadFromFile("addons/road_horizontal.png");
	textureRoadVertical.loadFromFile("addons/road_vertical.png");
	textureRoadAngle.loadFromFile("addons/road_angle.png");
	textureRoadInter.loadFromFile("addons/road_inter.png");
	textureMoney.loadFromFile("addons/piece.png");
	textureHp.loadFromFile("addons/coeur.png");
	sprRoadHorizontal = sf::Sprite(textureRoadHorizontal);
	sprRoadVertical = sf::Sprite(textureRoadVertical);
	sprRoadInter = sf::Sprite(textureRoadInter);
	sprRoadAngle = sf::Sprite(textureRoadAngle);
	sprMoney = sf::Sprite(textureMoney);
	sprHp = sf::Sprite(textureHp);
	sprRoadHorizontal.setScale(2.8125, 2.8125);
	sprRoadInter.setScale(2.8125, 2.8125);
	sprRoadVertical.setScale(2.8125, 2.8125);
	sprRoadAngle.setScale(2.8125, 2.8125);

	selectedTurret = AVAST;

	Road::createMap(roads,map,sprRoadHorizontal,sprRoadVertical,sprRoadAngle,sprRoadInter);

	for (int y = 0; y < sizeY; ++y)
	{
		for (int x = 0; x < sizeX; ++x)
		{
			bg.push_back(rand()%4);
		}
	}


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
					if (!trojans[j].isAlive())
					{
						money += TROJAN_VALUE;
						trojans.erase(trojans.begin() + j);
						--j;
					}
				}
			}
			for (int j = 0; j < usbKillers.size(); ++j)
			{
				if (projectiles[i].isAlive() && getDistance(usbKillers[j].getPos(), projectiles[i].getPos()) < 0.5)
				{
					usbKillers[j].hit(projectiles[i].getDamage());
					projectiles[i].kill();
					if (!usbKillers[j].isAlive())
					{
						money += USBKILLER_VALUE;
						usbKillers.erase(usbKillers.begin() + j);
						--j;
					}
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
					if (!trojans[j].isAlive())
					{
						money += TROJAN_VALUE;
						trojans.erase(trojans.begin() + j);
						--j;
					}
				}
			}
			for (int j = 0; j < usbKillers.size(); ++j)
			{
				if (getDistance(explosion, usbKillers[j].getPos()) < radius)
				{
					usbKillers[j].hit(damage);
					if (!usbKillers[j].isAlive())
					{
						money += USBKILLER_VALUE;
						usbKillers.erase(usbKillers.begin() + j);
						--j;
					}
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
			hp -= TROJAN_DAMAGE;
		}
	}

	for (int i = 0; i < usbKillers.size(); ++i)
	{
		if (!usbKillers[i].isAlive())
		{
			usbKillers.erase(usbKillers.begin() + i);
			--i;
			hp -= USBKILLER_DAMAGE;
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
		case AVAST_SHOP:
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
		case KASPERSKY_SHOP:
			if (money >= KASPERSKY_PRICE)
			{
				money -= KASPERSKY_PRICE;
				bool validPlace = true;
				for (int i = 0; i < turrets.size(); ++i)
				{
					if (turrets[i].getPos() == sf::Vector2f(posX, posY))
					{
						i = turrets.size();
						validPlace = false;
					}
				}
				if (validPlace)
					turrets.push_back(Turret(sf::Vector2i(posX, posY), &sprsKaspersky, KASPERSKY));

			}
			break;
		}
	}
}

void Game::sellTurret(int &mouseX, int& mouseY, sf::RenderWindow& rWindow, sf::View view)
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
}

void Game::beDraw(sf::RenderWindow& rWindow, sf::View const& view) 
{
	//rWindow.draw(sprBg);
	for (int y = 0; y < sizeY; ++y)
	{
		for (int x = 0; x < sizeX; ++x)
		{
			switch (rand()%4)
			{
			case 0:
				sprBg0.setPosition(x * 45, y * 45);
				rWindow.draw(sprBg0);
				break;
			case 1:
				sprBg1.setPosition(x * 45, y * 45);
				rWindow.draw(sprBg1);
				break;
			case 2:
				sprBg2.setPosition(x * 45, y * 45);
				rWindow.draw(sprBg2);
				break;
			case 3:
				sprBg3.setPosition(x * 45, y * 45);
				rWindow.draw(sprBg3);
				break;
			}
		}
	}
	for (int i = 0; i < roads.size(); ++i)
	{
		roads[i].beDraw(rWindow);
	}
	for (int i = 0; i < trojans.size(); ++i)
	{
		trojans[i].beDraw(rWindow);
	}
	for (int i = 0; i < usbKillers.size(); ++i)
	{
		usbKillers[i].beDraw(rWindow);
	}
	for (int i = 0; i < projectiles.size(); ++i)
	{
		projectiles[i].beDraw(rWindow);
	}
	for (int i = 0; i < mortars.size(); ++i)
	{
		mortars[i].beDraw(rWindow);
	}
	for (int i = 0; i < turrets.size(); ++i)
	{
		turrets[i].beDraw(rWindow);
	}


	//-------MENU MONEY-----------
	sf::RectangleShape rectInfo(sf::Vector2f(210.f, 130.f));
	//sf::FloatRect rectInfoRect = rectInfo.getLocalBounds();
    //rectInfo.setOrigin(rectInfoRect.width / 2.0f, rectInfoRect.height / 2.0f);
	rectInfo.setFillColor(sf::Color::White);
	rectInfo.setPosition(sf::Vector2f(10.f, 10.f));

	sf::Text textArgent;
	sf::Text textHp;
	sf::Text textVague;

	textVague.setFont(font);
	textArgent.setFont(font);
	textHp.setFont(font);
	
	//std::string 
	textVague.setFillColor(sf::Color::Black);
	textVague.setCharacterSize(18);
	textVague.setString("Vague " + std::to_string(level)); //
	textVague.setPosition(sf::Vector2f(20.f, 20.f));

	textArgent.setFillColor(sf::Color::Black);
	textArgent.setCharacterSize(17);
	textArgent.setString("$" + std::to_string(money));
	textArgent.setPosition(sf::Vector2f(50.f, 60.f));

	textHp.setFillColor(sf::Color::Black);
	textHp.setCharacterSize(17);
	textHp.setString(std::to_string(hp));
	textHp.setPosition(sf::Vector2f(50.f, 90.f));

	;
	sprMoney.setPosition(20, 60);
	sprMoney.setScale(0.08, 0.08);

	sprHp.setPosition(20, 90);
	sprHp.setScale(0.08, 0.08);

	
	rWindow.draw(rectInfo);
	rWindow.draw(textHp);
	rWindow.draw(sprHp);
	rWindow.draw(textArgent);
	rWindow.draw(sprMoney);
	rWindow.draw(textVague);

	

}

float getDistance(sf::Vector2f a, sf::Vector2f b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}