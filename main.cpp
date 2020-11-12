#include <iostream>
#include <SFML/graphics.hpp>
#include <SFML/System.hpp>

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
	sf::RenderWindow rWindow(sf::VideoMode(900,900),"Tower Defence");
	sf::Event event;
	sf::View view;
	// Salut, c'est le debut du jeu
	int gameMode = MENU;

	while (rWindow.isOpen())
	{

		//----------Modification de la taille de la vue pour ne pas "étirer" l'affichage
		while (rWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Resized)
			{
				if (rWindow.getSize().x > rWindow.getSize().y)//redimensionnement par ratio
				{
					view.setSize(sf::Vector2f(view.getSize().x, view.getSize().x * rWindow.getSize().y / rWindow.getSize().x));
				}
				else
				{
					view.setSize(sf::Vector2f(view.getSize().y * rWindow.getSize().x / rWindow.getSize().y, view.getSize().y));
				}
			}
		}
		sf::Mouse::getPosition();

		//------------------------------------------CHOIX MENU-------------------------------------------
		switch (gameMode)
		{
		case MENU:

			//--------------REFRESH MENU----------------------
			//menu.refresh(rWindow,       );


			break;
		case INGAME:
			
			//--------------REFRESH MENU----------------------



			break;
		}


	}
	return 0;
}