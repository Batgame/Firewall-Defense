#pragma once
#include "Projectile.h"
#include "Trojan.h"
#include "Turret.h"
#include "Mortar.h"

class Game
{
	int map;
	std::vector<Road> roads;
	std::vector<Projectile> projectiles;
	std::vector<Mortar> mortars;
	std::vector<Trojan> trojans;
	std::vector<Turret> turrets;
	int money;

	//sf::Texture texturebg;

public :

	Game(int map_ = 1);
	void refresh(sf::Time const& dt);
	void beDraw(sf::RenderWindow& rWindow) const;
	void refreshTurrets(sf::Time const& dt);
};