#include <iostream>
#include <SFML/graphics.hpp>
#include <SFML/System.hpp>
#include "header/Road.h"
#include "header/Trojan.h"
#include "header/Game.h"
#include "header/const.h"
#include "header/menu.h"
#include "header/const.h"
#include "header/TextureManager.h"
#include "header/Shop.h"
#include "header/constShop.h"


/*
							ENUMERATION :
	Une enumération est une sorte de "liste de define" par clef
	Chaque "define" sera changé après la compilation par un entier.
	L'avantage de l'enumeration est d'avoir une liste d'identifiant
	qui par définitions ne possède pas de doublons. De plus les identfiant
	qui vont remplacé les enumerations sont créée automatiquement (0,1,2,3,...)
*/

extern sf::Font font;


enum e_id_gamemode {
	MENU,
	INGAME,
    REGLES,
    GAME_OVER,
    LOADING,	//Risque de ne pas être utilisé (Pas de chargement nécessaire)
};


int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Firewall-Defense",sf::Style::Close);
    sf::View view(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    sf::Vector2i posSouris;
    sf::Vector2i mousePos;
    sf::Event event;
    
    sf::Image imgIcon;
    imgIcon.loadFromFile("addons/AvastShop.png");
    window.setIcon(16, 16, imgIcon.getPixelsPtr());

    Game game(1);
    sf::Clock clock;
    sf::Time dt;
    TextureManager::loadAllFont();
    bool flagClickLeft = false;
    bool flagClickRight = false;
    bool flag = false;
    bool flagEscape = false;
    int turretSel = 0;
    Shop magasin;
    int lastBestWave = 0;

    game.setSelectedTurret(AVAST);

    //-----------------IMAGE BACJGROUND----------------------------
    sf::Texture img_background;
    if (!img_background.loadFromFile("./addons/background_menu.png"))
    {
        std::cout << "Pb de chargement de l'image.\n" << std::endl;
    }
    sf::Sprite background;
    //background.setScale(0.42f, 0.25f);
    background.setScale(sf::Vector2f(view.getSize().x / img_background.getSize().x, view.getSize().y / img_background.getSize().y));
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
                            //printf("Voici les règles du jeu !\n");
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

                        break;
                    }
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                if (flagEscape)
                {
                    if (gameMode == INGAME)
                    {
                        gameMode = MENU;
                    }
                    else
                    {
                        window.close();
                    }
                    flagEscape = false;
                }
            }
            else
            {
                flagEscape = true;
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
            window.draw(background);
            drawMenu(window, posSouris, view);

            break;
        case REGLES:

            //--------------REFRESH MENU----------------------
            background_regles.setPosition(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2);
            window.draw(background);
            drowRegles(window, posSouris, view);

            break;
        case INGAME:
            //------------------Achat TOURELLE

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                mousePos = sf::Mouse::getPosition(window);

                //------------SHOP----------------------
                if (position_reel_x >= (BUTTON_POS.x - (0.5 * BUTTON_SIZE.x)) && position_reel_x <= BUTTON_POS.x + (0.5 * BUTTON_SIZE.x) && position_reel_y >= (BUTTON_POS.y - 0.5 * BUTTON_SIZE.y) && position_reel_y <= BUTTON_POS.y + 0.5 * BUTTON_SIZE.y) //sont dedans
                {
                    if (flag)
                    {
                        magasin.switchActive();
                        flag = false;
                    }
                }
                //----------------------------ACHAT TOURELLE-----------------------
                else if (flagClickLeft && !magasin.isOpenMenu())
                {
                    game.setSelectedTurret(turretSel);

                    flagClickLeft = false;

                    game.buyTurret(posSouris.x, posSouris.y, window, view);
                }
                else if (flagClickLeft && magasin.isOpenMenu())
                {
                    if (mousePos.x > (WIDTH / 4) * 3)
                    {
                        magasin.turretSelect(window, mousePos, turretSel);
                        flagClickLeft = false;
                    }
                    else
                    {
                        game.setSelectedTurret(turretSel);
                        game.buyTurret(posSouris.x, posSouris.y, window, view);
                        flagClickLeft = false;
                    }
                }
            }
            else
            {
                flag = true;
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
            if (game.isLoose())
            {
                gameMode = GAME_OVER;
                lastBestWave = game.getLevel();
                game.restart();
            }
            game.beDraw(window,view);
            magasin.beDraw(window, view);
            if(magasin.isOpenMenu())
            {
                magasin.turretExplain(window, turretSel);
            }
            break;
        case GAME_OVER:
            //-----------------------------------------------------Game Over------------------------------------------------------------
            sf::RectangleShape buttonContinuer(sf::Vector2f(LARGEUR_RECT, HAUTEUR_RECT));
            sf::FloatRect buttonContinuerRect = buttonContinuer.getLocalBounds();
            sf::Text textContinuer;
            sf::Text textGameOver;
            sf::Text textLastWave;

            textGameOver.setFont(font);
            textGameOver.setCharacterSize(100);
            textGameOver.setString("Game Over");
            sf::FloatRect textGameOverRect = textGameOver.getLocalBounds();
            textGameOver.setOrigin(textGameOverRect.width / 2.0f, textGameOverRect.height / 2.0f);
            textGameOver.setPosition(sf::Vector2f(WIDTH / 2, 150));
            textGameOver.setFillColor(sf::Color::White);

            textContinuer.setFont(font);
            textContinuer.setCharacterSize(TEXT_SIZE);
            textContinuer.setString("Continuer");
            sf::FloatRect textContinuerRect = textContinuer.getLocalBounds();
            textContinuer.setOrigin(textContinuerRect.width / 2.0f, textContinuerRect.height / 2.0f);
            textContinuer.setPosition(sf::Vector2f(WIDTH / 2, 0.75 * HEIGHT));
            textContinuer.setFillColor(sf::Color::White);

            textLastWave.setFont(font);
            textLastWave.setCharacterSize(TEXT_SIZE);
            textLastWave.setString("Vous avez tenu " + std::to_string(lastBestWave) + " vagues !");
            sf::FloatRect textLastwaveRect = textLastWave.getLocalBounds();
            textLastWave.setOrigin(textLastwaveRect.width / 2.0f, textLastwaveRect.height / 2.0f);
            textLastWave.setPosition(sf::Vector2f(WIDTH / 2, 0.5 * HEIGHT));
            textLastWave.setFillColor(sf::Color::White);


            buttonContinuer.setOrigin(buttonContinuerRect.width / 2.0f, buttonContinuerRect.height / 2.0f);
            buttonContinuer.setPosition(sf::Vector2f(WIDTH / 2, 0.75 * HEIGHT));
            buttonContinuer.setFillColor(sf::Color(32, 32, 32));
  

            if (isButtonSelect(window, posSouris, sf::Vector2f(WIDTH / 2, 0.75 * HEIGHT)))
            {
                if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                {
                    gameMode = MENU;
                }
                buttonContinuer.setFillColor(sf::Color(24, 26, 27));
                textContinuer.setFillColor(sf::Color::White);
            }
            
            window.draw(buttonContinuer);
            window.draw(textContinuer);
            window.draw(textGameOver);
            window.draw(textLastWave);
            break;
        }
        window.display();
        window.clear();
    }
}