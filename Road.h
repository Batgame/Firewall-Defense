#pragma once
#include <SFML/Graphics.hpp>

enum e_id_Direction
{

};

class Road
{
	sf::Vector2f pos;
	bool nextDirection[4]; //Définis pour chaque direcvtion en [i] si ce chemin est possible

public :

	void addNextDirection(int direction);
	void eraseNextDirection(int direction);
	Road(sf::Vector2f pos_ = sf::Vector2f(0, 0), bool tab[4] = false);
	int getNextRoad(sf::Vector2f const& position);
	void beDraw(sf::RenderWindow& rWindow);

};

