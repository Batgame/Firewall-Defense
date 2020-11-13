#pragma once
#include "Projectile.h"
#include "Trojan.h"

class Game
{
	int map;
	std::vector<Road> roads;
	std::vector<Projectile> projectiles;
	std::vector<Trojan> trojans;

public :

	Game(int map_ = 1);
	void refresh(sf::Time const& dt);
	void beDraw(sf::RenderWindow& rWindow);
};