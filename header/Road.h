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
	std::vector<int> nextDirection; //Définis pour chaque direction en [i] si ce chemin est possible
	static void drawLine(std::vector<Road>& path, sf::Vector2f a, sf::Vector2f b, sf::Sprite hor, sf::Sprite vert, sf::Sprite angle, sf::Sprite inter);

public :

	/*
		Fonction qui définis la route le chemin, avec id -> le numéro de map !
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
	/*
		Fonction inutilisé, cause : manque de temps (Change les sprites de road automatiquement)
	*/
	static void resetSprite(std::vector<Road>& roads,sf::Sprite hor,sf::Sprite vert, sf::Sprite angle, sf::Sprite inter);
	/*
		Retourne la quantité de chemin possible
	*/
	int getNextdirectionNb();
	/*
		Set le sprite de la road à une valeurs donnée	
	*/
	void setSprite(sf::Sprite spr_);
	/*	
		Retourne la position de la road
	*/
	sf::Vector2f getPos() const;
	/*
		Constructeur de la Road
	*/
	Road(sf::Sprite spr_,sf::Vector2f pos_ = sf::Vector2f(0, 0), std::vector<int> possiblePath = std::vector<int>());
	/*
		Donne le prochain suivant (de manière aléatoire si c'est une intersection)
	*/
	int getNextRoad() const;
	/*
		Retourne le tableau de direction
	*/
	std::vector<int> getNextRoadTab() const;
	/*
		Dessine la road
	*/
	void beDraw(sf::RenderWindow& rWindow);
};

