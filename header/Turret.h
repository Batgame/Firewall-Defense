#pragma once
#include "Projectile.h"
#include "Mortar.h"
#include "Animation.h"

enum e_id_Turret
{
	AVAST, //Tourelle Rapid mais peu de d�gat
	AVIRA, 
	WINDOW_DEFENDER,
	KASPERSKY
};

#define CD_AVAST 0.3f
#define DMG_AVAST 1
#define RANGE_AVAST 3

#define CD_KASPERSKY 2
#define DMG_KASPERSKY 10
#define RANGE_KASPERSKY 6

class Turret
{
	sf::Vector2i pos;
	float coolDown;
	float range;
	int damage;
	Animation anim;

public : 
	int id;

	Turret(sf::Vector2i pos_, Spritesheet* sprs, int id_ = 0);
	bool canShoot();
	void resfresh(sf::Time const& dt);
	Projectile createProjectile();
	Mortar createMortar(sf::Vector2f aim);
	sf::Vector2f getPos() const;
	float getRange();
	void beDraw(sf::RenderWindow& rWindow) const;
};