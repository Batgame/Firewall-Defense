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

	Animation(Spritesheet* sprs_, float duration_ = 1, float scaleX_ = 1, float scaleY_ = 1);
	void setDuration(float const& duration_);
	void setTimer(float const& timer_);
	float getTimer() const;
	void refresh(sf::Time dt);
	sf::Sprite getSprite() const;
	void beDraw(sf::RenderWindow& rWindow);

};

