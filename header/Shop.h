#pragma once

#include <SFML/Graphics.hpp>
#include "header/constShop.h"

class Shop
{
	//Variables
	bool isActive;
	int money;
	int idAchat;
	
	sf::RectangleShape shopDeve;
	sf::RectangleShape shopNoDeve;



	void buyTurret(int idAachat);


public :
	
	Shop();

	bool isOpenMenu(sf::RenderWindow& window, sf::Vector2i mousePos);

	
	void beDraw(sf::RenderWindow& window, sf::Vector2i mousePos, bool isActive, sf::Time dt);
};

