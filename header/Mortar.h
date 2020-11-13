#pragma once
#include "SFML/Graphics.hpp"

class Mortar
{
	sf::Vector2f pos;
	sf::Vector2f velocity;
	float flightDuration;
	float radius;

	int id;
	int damage;
	int speedMax;
	bool alive;

public:


	Mortar(sf::Vector2f pos_ = sf::Vector2f(0, 0), sf::Vector2f aim_ = sf::Vector2f(0, 0), int damage_ = 30);
	Mortar(float posX = 0, float posY = 0, float posXAim = 0,float posYAim = 0, int damage = 30);
	/*
		Fonction qui déplace le missile vers l'ennemie le plus proche
	*/
	void refresh(sf::Time const& dt);
	float getRadius();
	sf::Vector2f getPos()const;
	int getDamage();
	void beDraw(sf::RenderWindow& rWindow) const;
	bool isAlive();
};

