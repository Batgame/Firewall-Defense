#pragma once
#include "Projectile.h"
#include "Mortar.h"
#include "Animation.h"

enum e_id_Turret
{
	AVAST, //Tourelle Rapid mais peu de dégat
	WINDOW_DEFENDER,
	KASPERSKY
};

#define CD_AVAST 0.3f
#define DMG_AVAST 2
#define RANGE_AVAST 3

#define CD_KASPERSKY 2
#define DMG_KASPERSKY 5
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

	//Constructeur de la tourelle
	Turret(sf::Vector2i pos_, Spritesheet* sprs, int id_ = 0);
	//La tour peut tirer
	bool canShoot();
	//Refresh la tourelle en fonction du temps
	void resfresh(sf::Time const& dt);
	//Creer un projectile
	Projectile createProjectile();
	//Creer un mortier (Pour les tourelles Kaspersky)
	Mortar createMortar(sf::Vector2f aim);
	//Retourne la position de la tourelle
	sf::Vector2f getPos() const;
	//Donne le rayon d'action de la tourelle
	float getRange();
	//Dessine la tourelle
	void beDraw(sf::RenderWindow& rWindow) const;

};