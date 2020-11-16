#include <iostream>
#include <SFML/graphics.hpp>
#include <SFML/System.hpp>
#include "Road.h"
#include "Trojan.h"
#include "Game.h"
#include "const.h"
#include "menu.h"
#include "const.h"
#include "TextureManager.h"

/*
							ENUMERATION :
	Une enum�ration est une sorte de "liste de define" par clef
	Chaque "define" sera chang� apr�s la compilation par un entier.
	L'avantage de l'enumeration est d'avoir une liste d'identifiant
	qui par d�finitions ne poss�de pas de doublons. De plus les identfiant
	qui vont remplac� les enumerations sont cr��e automatiquement (0,1,2,3,...)
*/

enum e_id_gamemode {
	MENU,
	INGAME,
    REGLES,
	LOADING,	//Risque de ne pas �tre utilis� (Pas de chargement n�cessaire)
};


int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Firewall-Defense");
    sf::View view(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    sf::Vector2i posSouris;
    sf::Event event;
    Game game(1);
    sf::Clock clock;
    sf::Time dt;
    TextureManager::loadAllFont();
    bool flagClickLeft = true;
    bool flagClickRight = true;
    game.setSelectedTurret(AVAST);
    //-----------------IMAGE BACJGROUND----------------------------
    sf::Texture img_background;
    if (!img_background.loadFromFile("./addons/test2.jpg"))
    {
        std::cout << "Pb de chargement de l'image.\n" << std::endl;
    }
    sf::Sprite background;
    //background.setScale(0.42f, 0.25f);
    background.setScale(1, 1);
    background.setOrigin(0, 0);
    background.setTexture(img_background);

    //------------------SECOND BACKGROUND------------------------
    sf::Texture image_regles;
    if (!image_regles.loadFromFile("./addons/neon_rose.jpg"))
    {
        std::cout << "Pb de chargement de l'image.\n" << std::endl;
    }
    sf::Sprite background_regles;
    //background.setScale(0.42f, 0.25f);
    background_regles.setScale(1, 1);
    background_regles.setOrigin(0, 0);
    background_regles.setTexture(image_regles);


    //-------------FIN IMAGE BACKGROUND----------------------------
    int gameMode = MENU;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {

            //-----------------Event Fermeture-------------------
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            //-----------------Event souris-------------------
            if (event.type == sf::Event::MouseButtonPressed)
            {

                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    switch (gameMode)
                    {
                    case MENU:

                        if (isButtonSelect(window, posSouris, BUTTON_POS_PLAY))
                        {
                            gameMode = INGAME;
                            //printf("On joue ! \n");
                        }
                        else if (isButtonSelect(window, posSouris, BUTTON_POS_OPT))
                        {
                            //printf("Nous sommes dans les options !\n");
                        }
                        else if (isButtonSelect(window, posSouris, BUTTON_POS_RGL))
                        {
                            gameMode = REGLES;
                            //printf("Voici les r�gles du jeu !\n");
                        }
                        else if (isButtonSelect(window, posSouris, BUTTON_POS_EXT))
                        {
                            window.close();
                        }
                        break;

                    case REGLES:
                        if (isButtonSelect(window, posSouris, BUTTON_POS_RET))
                        {
                            gameMode = MENU;
                            std::cout << "Retour au menu ! \n" << std::endl;
                        }
                        break;

                    }
                }
            }
        }

        dt = clock.restart();


        if (window.getSize().x < window.getSize().y)  //redimensionnement par ratio
        {
            view.setSize(sf::Vector2f(SCREEN_WIDTH, view.getSize().x * window.getSize().y / window.getSize().x));
        }
        else
        {
            view.setSize(sf::Vector2f(view.getSize().y * window.getSize().x / window.getSize().y, SCREEN_HEIGHT));
        }

        int position_reel_y = window.mapPixelToCoords(sf::Mouse::getPosition(window), view).y;
        int position_reel_x = window.mapPixelToCoords(sf::Mouse::getPosition(window), view).x;
        posSouris.x = position_reel_x;
        posSouris.y = position_reel_y;
        window.setView(view);


        switch (gameMode)
        {
        case MENU:

            //--------------REFRESH MENU----------------------
            //menu.refresh(rWindow,);
            background.setPosition(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2);
            background.setScale(view.getSize().x / img_background.getSize().x, view.getSize().y / img_background.getSize().y);
            window.draw(background);
            drawMenu(window, posSouris, view);

            break;
        case REGLES:

            //--------------REFRESH MENU----------------------
            background_regles.setPosition(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2);
            window.draw(background_regles);
            drowRegles(window, posSouris, view);

            break;
        case INGAME:

            //------------------Achat TOURELLE

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                if (flagClickLeft)
                {
                    game.buyTurret(posSouris.x,posSouris.y,window,view);
                    flagClickLeft = false;
                }
            }
            else
            {
                flagClickLeft = true;
            }


            //------------------Vente TOURELLE


            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
            {
                if (flagClickRight)
                {
                    game.sellTurret(posSouris.x, posSouris.y, window, view);
                    flagClickRight = false;
                }
            }
            else
            {
                flagClickRight = true;
            }
            game.refresh(dt);
            game.beDraw(window,view);
            break;
        }
        window.display();
        window.clear();
    }
}