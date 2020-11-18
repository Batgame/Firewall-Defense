#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Spritesheet
{
	sf::Texture texture;
	unsigned int sizeX;
	unsigned int sizeY;
	unsigned int nbSpriteX;
	unsigned int nbSpriteY;
	unsigned int sizeSpriteX;
	unsigned int sizeSpriteY;
	std::string fileName;

	std::vector<sf::Sprite> sprites;

public : 
	
	/*
		Constructeur de la sritesheet
	*/

	Spritesheet(std::string fileName_,unsigned int nbSpriteX_ = 1, unsigned int nbSpriteY_ = 1);
	/*
		Donne le nombre total de sprite
	*/
	unsigned int getTotalSprite();
	/*
		Retourne le sprite demandé
	*/
	sf::Sprite getSprite(int nbPos);
};

