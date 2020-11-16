#pragma once
#include "Projectile.h"
#include "Trojan.h"
#include "Turret.h"
#include "Mortar.h"
#include "Spritesheet.h"

#define DELAY_SPAWN 0.3


class Game
{
	Spritesheet sprsAvast;


	float delaySpawn;
	int map;
	std::vector<Road> roads;
	std::vector<Projectile> projectiles;
	std::vector<Mortar> mortars;
	std::vector<Trojan> trojans;
	std::vector<Turret> turrets;
	int trojanCount;
	int money;
	int level;

	//sf::Texture texturebg;

public :

	Game(int map_ = 1);
	void refresh(sf::Time& dt);
	void beDraw(sf::RenderWindow& rWindow) const;
	void refreshTurrets(sf::Time const& dt);
};