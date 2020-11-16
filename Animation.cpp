#include "header/Animation.h"
#include "header/Spritesheet.h"
#include <SFML/Graphics.hpp>

Animation::Animation(Spritesheet* sprs_, float duration_, float scaleX_, float scaleY_) : sprs(sprs_), duration(duration_),timer(0),scaleX(scaleX_), scaleY(scaleY_)
{
	
}

void Animation::setDuration(float const& duration_)
{
	duration = duration_;
}

void Animation::setTimer(float const& timer_)
{
	timer = timer_;
}

float Animation::getTimer() const
{
	return timer;
}

void Animation::refresh(sf::Time dt)
{
	timer += dt.asSeconds();
	if (timer >= duration)
	{
		timer = 0;
	}
}

sf::Sprite Animation::getSprite() const
{
	sf::Sprite spr = sprs->getSprite(sprs->getTotalSprite() * timer / duration);

	spr.setScale(scaleX,scaleY);

	return spr;
}

void Animation::beDraw(sf::RenderWindow& rWindow)
{
	rWindow.draw(getSprite());
}
