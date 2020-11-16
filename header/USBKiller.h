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

	USBKiller(Spritesheet* sprs,sf::Vector2f pos = sf::Vector2f(0, 0), int direction = 0);
	void refresh(sf::Time const& dt, std::vector<Road>& roads);
	void beDraw(sf::RenderWindow& rWindow) const;
	void hit(int damage);
	bool isAlive();
	sf::Vector2f getPos();
	sf::Vector2f getFuturePos();
	//bool doCollide(std::vector);
};

