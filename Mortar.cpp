#include "Mortar.h"
#include "Projectile.h"

Mortar::Mortar(sf::Vector2f pos_, sf::Vector2f aim_, int damage_):pos(pos_),damage(damage_),velocity(sf::Vector2f(aim_.x - pos.x, aim_.y - pos.y)),flightDuration(0),radius(1)
{

}

Mortar::Mortar(float posX, float posY, float posXAim, float posYAim, int damage_):pos(sf::Vector2f(posX,posY)), velocity(sf::Vector2f(posXAim - pos.x, posYAim - pos.y)),damage(damage_),flightDuration(0), radius(1)
{

}

void Mortar::refresh(sf::Time const& dt)
{
	flightDuration += dt.asSeconds();

	pos.x += velocity.x * dt.asSeconds();
	pos.y += velocity.y * dt.asSeconds();
	if (flightDuration > 1)
	{
		alive = false;
	}
}

float Mortar::getRadius()
{
	return radius;
}

sf::Vector2f Mortar::getPos() const
{
	return pos;
}

int Mortar::getDamage()
{
	return damage;
}

void Mortar::beDraw(sf::RenderWindow& rWindow) const
{
	sf::CircleShape c;
	c.setRadius(10);
	c.setFillColor(sf::Color::Red);
	c.setPosition(pos.x * 45 - 5, pos.y * 45 - 5);
	rWindow.draw(c);
}

bool Mortar::isAlive()
{
	return alive;
}
