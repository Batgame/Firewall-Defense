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

	Spritesheet(std::string fileName_,unsigned int nbSpriteX_ = 1, unsigned int nbSpriteY_ = 1);
	unsigned int getTotalSprite(); //A single Sprite size
	sf::Sprite getSprite(int nbPos);
};

