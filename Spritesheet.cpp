#include "Spritesheet.h"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

Spritesheet::Spritesheet(std::string fileName_, unsigned int nbSpriteX_, unsigned int nbSpriteY_):
fileName(fileName_),nbSpriteX(nbSpriteX_),nbSpriteY(nbSpriteY_)
{
	if (!texture.loadFromFile(fileName))
	{
		std::cout << "The texture : "<< fileName << " is missing" << std::endl;
	}

	sizeX = texture.getSize().x;
	sizeY = texture.getSize().y;

	sizeSpriteX = sizeX / nbSpriteX;
	sizeSpriteY = sizeY / nbSpriteY;

	sf::Sprite spr;
	int posX = 0;
	int posY = 0;

	for (int i = 0; i < nbSpriteX * nbSpriteY; i++)
	{
		sf::IntRect rect = sf::IntRect(posX, posY, sizeSpriteX, sizeSpriteY);

		posX = (i * sizeSpriteX) % sizeX;
		posY = (i * sizeSpriteY) / sizeX;

		spr = sf::Sprite(texture, rect);
		sprites.push_back(spr);
	}
}

unsigned int Spritesheet::getTotalSprite()
{
	return nbSpriteX * nbSpriteY;
}

sf::Sprite Spritesheet::getSprite(int nbPos)
{
	return sprites[nbPos];
}
