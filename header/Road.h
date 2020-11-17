#pragma once
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
	sf::Sprite spr;
	sf::Vector2f pos;
	std::vector<int> nextDirection; //D�finis pour chaque direction en [i] si ce chemin est possible
	static void drawLine(std::vector<Road>& path, sf::Vector2f a, sf::Vector2f b, sf::Sprite hor, sf::Sprite vert, sf::Sprite angle, sf::Sprite inter);

public :

	/*
		Fonction qui d�finis la route le chemin, avec id -> le num�ro de map !
	*/
	static void createMap(std::vector<Road>& map, int id, sf::Sprite hor, sf::Sprite vert, sf::Sprite angle, sf::Sprite inter);
	/*
		Rajoute une direction
	*/
	void addNextDirection(int const& direction);
	/*
		Supprime une direction
	*/
	void eraseNextDirection(int const& direction);

	/*
		Cherche l'id de la Road correspndante
	*/
	static int getId(std::vector<Road>& map, sf::Vector2i const& pos_);
	static void resetSprite(std::vector<Road>& roads,sf::Sprite hor,sf::Sprite vert, sf::Sprite angle, sf::Sprite inter);
	int getNextdirectionNb();

	void setSprite(sf::Sprite spr_);
	sf::Vector2f getPos() const;
	Road(sf::Sprite spr_,sf::Vector2f pos_ = sf::Vector2f(0, 0), std::vector<int> possiblePath = std::vector<int>());
	int getNextRoad() const;
	std::vector<int> getNextRoadTab() const;
	void beDraw(sf::RenderWindow& rWindow);
};

