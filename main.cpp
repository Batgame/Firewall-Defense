#include <iostream>
#include <SFML/graphics.hpp>
#include <SFML/System.hpp>
#include "Road.h"
#include "Trojan.h"
#include "Game.h"

/*
							ENUMERATION :
	Une enumération est une sorte de "liste de define" par clef
	Chaque "define" sera changé après la compilation par un entier.
	L'avantage de l'enumeration est d'avoir une liste d'identifiant
	qui par définitions ne possède pas de doublons. De plus les identfiant
	qui vont remplacé les enumerations sont créée automatiquement (0,1,2,3,...)
*/

enum e_id_gamemode {
	MENU,
	INGAME,
	LOADING,	//Risque de ne pas être utilisé (Pas de chargement nécessaire)
};


int main()
{
	sf::RenderWindow rWindow(sf::VideoMode(900,900),"Firewall Defense");
	sf::Event event;
	sf::View view(sf::Vector2f(450,450),sf::Vector2f(900,900));
	int gameMode = INGAME;
	Game game(1);
	sf::Clock clock;
	sf::Time dt;
	
	
	while (rWindow.isOpen())
	{
		//----------Modification de la taille de la vue pour ne pas "étirer" l'affichage
	
		while (rWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Resized)
			{
				if (rWindow.getSize().x < rWindow.getSize().y)//redimensionnement par ratio
				{
					view.setSize(sf::Vector2f(900, view.getSize().x * rWindow.getSize().y / rWindow.getSize().x));
				}
				else
				{

					view.setSize(sf::Vector2f(view.getSize().y * rWindow.getSize().x / rWindow.getSize().y, 900));
				}
			}
		}if (event.type == sf::Event::Closed)
		{
			rWindow.close();
		}

		//---delta time :

		dt = clock.restart();


		//------------------------------------------CHOIX MENU-------------------------------------------
		switch (gameMode)
		{
		case MENU:

			//--------------REFRESH MENU----------------------
			//menu.refresh(rWindow,);
			



			break;
		case INGAME:
			
			//--------------REFRESH MENU----------------------
			game.refresh(dt);
			game.beDraw(rWindow);

			break;
		}
		rWindow.setView(view);
		rWindow.display();
		rWindow.clear();
	}
	return 0;
}