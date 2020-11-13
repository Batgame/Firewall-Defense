#include "Turret.h"
#include "Projectile.h"
#include "Mortar.h"

Turret::Turret(sf::Vector2i pos_, int id_):id(id_),pos(pos_)
{
	switch (id)
	{
	case AVAST:
		range = RANGE_AVAST;
		break;
	case KASPERSKY:
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
	}
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

	case AVIRA:

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
