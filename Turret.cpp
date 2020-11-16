#include "Turret.h"
#include "Projectile.h"
#include "Mortar.h"
#include "TextureManager.h"
#include "Spritesheet.h"
#include "Animation.h"



Turret::Turret(sf::Vector2i pos_,Spritesheet* sprs, int id_):id(id_),pos(pos_),anim(Animation(sprs, CD_AVAST, 2.8125, 2.8125))
{
	switch (id)
	{
	case AVAST:
		range = RANGE_AVAST;
		break;
	case KASPERSKY:
		anim.setDuration(CD_KASPERSKY);
		range = RANGE_KASPERSKY;
		break;
	}
}


bool Turret::canShoot()
{
	return coolDown == 0;
}

void Turret::resfresh(sf::Time const& dt)
{
	coolDown -= dt.asSeconds();

	if (coolDown < 0)
	{
		coolDown = 0;
		anim.setTimer(0);
	}else 
	anim.refresh(dt);

}

Projectile Turret::createProjectile()
{
	Projectile projectile = Projectile(pos.x + 0.5,pos.y + 0.5);
	switch (id)
	{
	case AVAST:
		projectile = Projectile(pos.x + 0.5, pos.y + 0.5,DMG_AVAST,AVAST_BULLET);
			coolDown = CD_AVAST;
		break;
	}
	return projectile;
}


Mortar Turret::createMortar(sf::Vector2f aim)
{
	coolDown = CD_KASPERSKY;

	return Mortar(pos.x + 0.5, pos.y + 0.5, aim.x, aim.y,DMG_KASPERSKY);
}

sf::Vector2f Turret::getPos() const
{
	return sf::Vector2f(pos.x,pos.y);
}

float Turret::getRange()
{
	return range;
}

void Turret::beDraw(sf::RenderWindow& rWindow) const
{
	sf::Sprite spr = anim.getSprite();
	spr.setPosition(pos.x * 45, pos.y * 45);
	rWindow.draw(spr);
}
