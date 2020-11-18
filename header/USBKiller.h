#pragma once
#include <SFML/Graphics.hpp>
#include "Road.h"
#include <SFML/Graphics.hpp>
#include "Animation.h"

#define HP 10
#define SPEED_MAX 2	//Speed en bloc/sec

class USBKiller
{
	sf::Vector2f pos;
	int direction;
	float distanceToWalk;
	float speed;
	int hp;
	Animation anim;

public:

	//Constructeur des usbKiller
	USBKiller(Spritesheet* sprs,sf::Vector2f pos = sf::Vector2f(0, 0), int direction = 0);
	//Constructeur des usbKiller
	void refresh(sf::Time const& dt, std::vector<Road>& roads);
	//Dessine l'usbKiller
	void beDraw(sf::RenderWindow& rWindow) const;
	//Inflige des degats a l'usbKiller
	void hit(int damage);
	//Demande si le joueur est vivant
	bool isAlive();
	//retourne la position de l'usbKiller
	sf::Vector2f getPos();
	//Retourne la position de l'usbKiller
	sf::Vector2f getFuturePos();
};

