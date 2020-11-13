#pragma once
#include <SFML/Graphics.hpp>

enum e_id_Projectile
{
	MISSILE,
};

class Projectile
{
	sf::Vector2f pos;
	 
	int id;
	int damage;
	int speedMax;
	bool alive;

public :
	
	
	Projectile(sf::Vector2f pos_ = sf::Vector2f(0,0), int id_ = MISSILE, float speedMax_ = 8);
	/*
		Fonction qui déplace le missile vers l'ennemie le plus proche
	*/
	void refresh(sf::Time const& dt, sf::Vector2f& aim);

	/*
		Fonction qui donne le vecteur a en format POLAIRE (X = angle, Y = norme) DEPUIS un a en format CARTESIEN
	*/
	sf::Vector2f getPolarVector(sf::Vector2f a);
	/*
		Fonction qui donne le vecteur a en format CARTESIEN DEPUIS un a en format POLAIRE
	*/
	sf::Vector2f getVector(sf::Vector2f a);
	sf::Vector2f getPos()const;
	int getDamage();
	void beDraw(sf::RenderWindow& rWindow);
	void kill();
	bool isAlive();
};

