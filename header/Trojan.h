#pragma once
#include <SFML/Graphics.hpp>
#include "Road.h"
#include <SFML/Graphics.hpp>
#include "Animation.h"

#define HP 40
#define SPEED_MAX 2	//Speed en bloc/sec

class Trojan
{
	sf::Vector2f pos;
	int direction;
	float distanceToWalk;
	float speed;
	int hp;
	Animation anim;

public :



	//Constructeur de la classe Trojan
	Trojan(Spritesheet *sprs,sf::Vector2f pos = sf::Vector2f(0,0),int direction = 0, int hp_ = HP);
	//Refresh le Trojan en fonction du temps
	void refresh(sf::Time const& dt,std::vector<Road>& roads);
	//Dessine le Trojan
	void beDraw(sf::RenderWindow& rWindow) const;
	//Fait prendre des degats au Trojan
	void hit(int damage);
	//Retourne si le Trojan est en vie
	bool isAlive();
	//retourne la position de la position
	sf::Vector2f getPos();
	//Retourne la position futur du Trojan (Pos + 1sec)
	sf::Vector2f getFuturePos();
};

