#pragma once

#include <SFML/Graphics.hpp>
#include "header/constShop.h"


enum e_id_turretSel
{
	EXPLAIN_SHOP,
	AVAST_SHOP,
	KASPERSKY_SHOP,
	DEFENDER_SHOP,
	MCAFEE_SHOP,
};

class Shop
{
	//Variables
	bool isActive;
	int money;
	int idAchat;

	int turretSel = 0;

	sf::RectangleShape shopDeve;
	sf::RectangleShape shopNoDeve;
	sf::RectangleShape barre;

	sf::RectangleShape turret_1;
	sf::RectangleShape turret_2;
	sf::RectangleShape turret_3;
	sf::RectangleShape turret_4;

	sf::Texture txtTurret1;
	sf::Sprite sprTurret1;

	sf::Texture txtTurret2;
	sf::Sprite sprTurret2;

	sf::Texture txtTurret3;
	sf::Sprite sprTurret3;

	sf::Texture txtTurret4;
	sf::Sprite sprTurret4;

	sf::RectangleShape turret_explain;

public :
	
	/*
		Constructeur du shop
		*/
	Shop();
	/*
	Retourne si le shop est ouvert ou non
	*/
	bool isOpenMenu();
	/*
	Dessine le shop
	*/
	void beDraw(sf::RenderWindow& window,sf::View view);
	/*
		Switch l'ouverture du shop
	*/
	void switchActive();
	/*
		Change la sélection de Tourelle en fonction d'ou on clique (valeurs par référence)
	*/
	int turretSelect(sf::RenderWindow& window, sf::Vector2i mousePos, int& turretSelect);
	/*
		Switch l'ouverture du shop
	*/
	void turretExplain(sf::RenderWindow& window, int turretSelect);
};

