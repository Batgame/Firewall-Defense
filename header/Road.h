#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

enum e_id_Direction
{
	UP = 0,
	RIGHT = 1,
	DOWN = 2,
	LEFT = 3
};

class Road
{
	sf::Vector2f pos;
	std::vector<int> nextDirection; //Définis pour chaque direction en [i] si ce chemin est possible
	static void drawLine(std::vector<Road>& path, sf::Vector2f a, sf::Vector2f b);


public :

	static void createMap(std::vector<Road>& map, int id);
	void addNextDirection(int direction);
	void eraseNextDirection(int direction);
	Road(sf::Vector2f pos_ = sf::Vector2f(0, 0), std::vector<int> possiblePath = std::vector<int>());
	int getNextRoad(sf::Vector2f const& position);
	void beDraw(sf::RenderWindow& rWindow);

};

