#pragma once
#include <SFML/Graphics.hpp>
#include "Road.h"
#include <SFML/Graphics.hpp>

#define HP 2000
#define SPEED_MAX 3	//Speed en bloc/sec

class Trojan
{
	sf::Vector2f pos;
	int direction;
	float distanceToWalk;
	float speed;
	int hp;

public :

	Trojan(sf::Vector2f pos = sf::Vector2f(0,0),int direction = 0, int hp_ = HP);
	void refresh(sf::Time const& dt,std::vector<Road>& roads);
	void beDraw(sf::RenderWindow& rWindow);
	void hit(int damage);
	bool isAlive();
	sf::Vector2f getPos();
	//bool doCollide(std::vector);
};

