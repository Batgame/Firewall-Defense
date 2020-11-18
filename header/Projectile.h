#pragma once
#include <SFML/Graphics.hpp>

enum e_id_Projectile
{
	MISSILE,
	AVAST_BULLET,

};

	/*
		Fonction qui donne le vecteur a en format POLAIRE (X = angle, Y = norme) DEPUIS un a en format CARTESIEN
	*/
	sf::Vector2f getPolarVector(sf::Vector2f a);
	/*
		Fonction qui donne le vecteur a en format CARTESIEN DEPUIS un a en format POLAIRE
	*/
	sf::Vector2f getVector(sf::Vector2f a);

class Projectile
{
	sf::Vector2f pos;
	 
	int id;
	int damage;
	int speedMax;
	bool alive;

public :
	
	//Constructeur
	Projectile(sf::Vector2f pos_ = sf::Vector2f(0, 0), int id_ = MISSILE, int damage = 2, float speedMax_ = 8);
	Projectile(float posX = 0, float posY = 0, int id_ = MISSILE, int damage = 2, float speedMax_ = 8);
	/*
		Fonction qui déplace le missile vers l'ennemie le plus proche
	*/
	void refresh(sf::Time const& dt, sf::Vector2f& aim);

	//Retourne la position du joueur
	sf::Vector2f getPos()const;
	//Retourne la cible 
	sf::Vector2f getAim() const;
	//Retourne les degats du projectile
	int getDamage();
	//Dessine le projectile
	void beDraw(sf::RenderWindow& rWindow) const;
	//Tue le projectile
	void kill();
	//Retourne true si le Projectile est vivant 
	bool isAlive();
};

