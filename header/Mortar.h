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

	//Constructeurs du mortier
	Mortar(sf::Vector2f pos_ = sf::Vector2f(0, 0), sf::Vector2f aim_ = sf::Vector2f(0, 0), int damage_ = 30);
	Mortar(float posX = 0, float posY = 0, float posXAim = 0,float posYAim = 0, int damage = 30);
	/*
		Fonction qui déplace le missile vers l'ennemie le plus proche
	*/
	void refresh(sf::Time const& dt);
	//Retourne le rayon d'eplosion du mortier
	float getRadius();
	//Retourne la position du mortier
	sf::Vector2f getPos()const;
	//Retourne les degats du mortier
	int getDamage();
	//Dessine le mortier
	void beDraw(sf::RenderWindow& rWindow) const;
	//Retourne vrai si le mortier est encore en déplacement
	bool isAlive();
};

