#pragma once

#include <SFML/Graphics.hpp>
#include "Shop.h"
#include "constShop.h"

class Shop
{
	//Variables
	bool isActive;
	int money;
	int idAchat;

	void buyTurret(int idAachat);


public :
	
	Shop();

	bool isOpenMenu(sf::RenderWindow& window, sf::Vector2i mousePos);

	
	void beDraw(sf::RenderWindow& window, sf::Vector2i mousePos, bool isActive);
};

