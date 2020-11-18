#pragma once
#include "Spritesheet.h"
#include <SFML/Graphics.hpp>

class Animation
{

	Spritesheet* sprs;
	float duration;
	float timer;
	float scaleX;
	float scaleY;

public :

	//Constructeur de la classe spritesheet
	Animation(Spritesheet* sprs_, float duration_ = 1, float scaleX_ = 1, float scaleY_ = 1);
	//Setup la durée total de l'animation
	void setDuration(float const& duration_);
	//Setup le timer
	void setTimer(float const& timer_);
	//Donne le temps t de l'animation
	float getTimer() const;
	//Refresh l'animation dans le temps
	void refresh(sf::Time dt);
	//Retourne le sprite de l'instant 
	sf::Sprite getSprite() const;
	//Dessine le sprite sur l'ecran
	void beDraw(sf::RenderWindow& rWindow);

};

