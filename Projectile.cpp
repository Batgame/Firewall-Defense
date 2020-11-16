#include "header/Projectile.h"
#define PI 3.14159265358979323

Projectile::Projectile(sf::Vector2f pos_, int id_,int damage_ ,float speedMax_) : pos(pos_), speedMax(speedMax_), id(id_), alive(true),damage(damage_)
{

}
Projectile::Projectile(float posX, float posY, int id_, int damage_, float speedMax_) : pos(sf::Vector2f(posX,posY)), speedMax(speedMax_), id(id_), alive(true), damage(damage_)
{
}
void Projectile::refresh(sf::Time const& dt, sf::Vector2f& aim)
{
	sf::Vector2f v = sf::Vector2f(aim.x - pos.x, aim.y - pos.y);
    v = getPolarVector(v);
    v.y = speedMax;
    v = getVector(v);

	pos.x += dt.asSeconds() * v.x;
	pos.y += dt.asSeconds() * v.y;
}

sf::Vector2f getVector(sf::Vector2f a) //x -> alpha, y -> norme
{
    while (a.x > (PI * 2))
        a.x -= (PI * 2);

    if (a.x < PI / 2)
    {
        return sf::Vector2f(sin(a.x) * a.y, cos(a.x) * -a.y);
    }
    else if (a.x < PI)
    {
        return sf::Vector2f(cos(a.x - PI / 2) * a.y, sin(a.x - PI / 2) * a.y);
    }
    else if (a.x < PI * 1.5)
    {
        return sf::Vector2f(-sin(a.x - PI) * a.y, cos(a.x - PI) * a.y);
    }

    return sf::Vector2f(-cos(a.x - PI * 1.5) * a.y, -sin(a.x - PI * 1.5) * a.y);

}


sf::Vector2f Projectile::getPos() const
{
    return pos;
}

int Projectile::getDamage()
{
    return damage;
}

void Projectile::beDraw(sf::RenderWindow& rWindow) const
{
    sf::CircleShape c;
    c.setRadius(5);
    c.setFillColor(sf::Color::Red);
    c.setPosition(pos.x * 45 - 5, pos.y * 45 - 5);
    rWindow.draw(c);
}

void Projectile::kill()
{
    alive = false;
}

bool Projectile::isAlive()
{
    return alive;
}

sf::Vector2f getPolarVector(sf::Vector2f a)
{
    if (a.x > 0 && a.y < 0)
    {
        return sf::Vector2f(atan(a.x / -a.y), sqrt(a.x * a.x + a.y * a.y));
    }
    else if (a.x > 0 && a.y > 0)
    {
        return sf::Vector2f(atan(a.y / a.x) + PI / 2, sqrt(a.x * a.x + a.y * a.y));
    }
    else if (a.x < 0 && a.y > 0)
    {
        return sf::Vector2f(atan(-a.x / a.y) + PI, sqrt(a.x * a.x + a.y * a.y));
    }
    return sf::Vector2f(atan(a.y / a.x) + 1.5 * PI, sqrt(a.x * a.x + a.y * a.y));
}
