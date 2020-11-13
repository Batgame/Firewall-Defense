#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "header/const.h"
#include "header/menu.h"



/*
------------------------------------TO DO-----------------------------------------------------
- faire un truc plus disign
- centrer le texte sur bouton (il y a peut etre une fonction qui permet de le faire mais je l'ai pas trouvé(c'est mathis qui me l'a dis))
- Faire la continuité du menu lorsque l'on clique sur les boutons
*/



int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Firewall-Defense");
    sf::View view(sf::Vector2f(450, 450), sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

    sf::Texture img_background;
    sf::Vector2i posSouris;
    sf::Event event;

    //-----------------IMAGE BACJGROUND----------------------------
	if (!img_background.loadFromFile("./addons/background.jpg"))
	{
		printf("Pb de chargement de l'image.\n");
	}
	sf::Sprite background;
	background.setScale(0.5f, 0.5f);
	background.setOrigin(0, 0);
	background.setTexture(img_background);

    //-------------FIN IMAGE BACKGROUND----------------------------
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
            //--------------------------Resise de la fenêtre----------------------------------
            if (event.type == sf::Event::Resized)
            {
                if (window.getSize().x < window.getSize().y)  //redimensionnement par ratio
                {
                    view.setSize(sf::Vector2f(900, view.getSize().x * window.getSize().y / window.getSize().x));
                }
                else
                {

                    view.setSize(sf::Vector2f(view.getSize().y * window.getSize().x / window.getSize().y, 900));
                }
            }

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
                    if (isButtonSelect(window, posSouris, BUTTON_POS_PLAY))
                    {
                        printf("On joue ! \n");
                    }
                    else if (isButtonSelect(window, posSouris, BUTTON_POS_OPT))
                    {
                        printf("Nous sommes dans les options !\n");
                    }
                    else if (isButtonSelect(window, posSouris, BUTTON_POS_RGL))
                    {
                        printf("Voici les règles du jeu !\n");
                    }
                    else if (isButtonSelect(window, posSouris, BUTTON_POS_EXT))
                    {
                        window.close();
                    }
                }
            }
		}


        posSouris = sf::Mouse::getPosition(window);


		window.clear();
		window.draw(background);
        beDraw(window, posSouris);
		window.display();
	}
}

//---------------------------------FONCTIONS---------------------------
/*
La fonction dessine : 
    - Les Rectangles
    - Les textes
    - Les changements de couleurs des boutons lorsque la souris passes dessus
    - Les changements de couleurs de texte lorsque la souris passe dessus ( /!\ TO DO /!\ )
*/
void beDraw(sf::RenderWindow& window, sf::Vector2i& posSouris)
{
    sf::RectangleShape buttonPlay(sf::Vector2f(LARGEUR_RECT, HAUTEUR_RECT));
    sf::RectangleShape buttonOptions(sf::Vector2f(LARGEUR_RECT, HAUTEUR_RECT));
    sf::RectangleShape buttonRegles(sf::Vector2f(LARGEUR_RECT, HAUTEUR_RECT));
    sf::RectangleShape buttonExit(sf::Vector2f(LARGEUR_RECT, HAUTEUR_RECT));
    sf::Font font;
    sf::Text textTitre;
    sf::Text textJouer;
    sf::Text textOption;
    sf::Text textRegles;
    sf::Text textExit;

    //INITIALISATION
    textTitre.setFont(font);
    textJouer.setFont(font);
    textOption.setFont(font);
    textRegles.setFont(font);
    textExit.setFont(font);

    //--------------------POLICE-------------------------
    if (!font.loadFromFile("./addons/font.ttf")) {

        printf("Impossible de charger les font.\n");
    }

    //DEBUT TITRE
    textTitre.setString("Firewall-Defense");
    textTitre.setCharacterSize(100);
    textTitre.setFillColor(sf::Color::Black);
    sf::FloatRect textRect = textTitre.getLocalBounds();
    textTitre.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    textTitre.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, 100));
    //FIN TITRE

    //DEBUT MENU
    //-----------JOUER----------------
    textJouer.setString("Jouer");
    textJouer.setCharacterSize(50);
    textJouer.setFillColor(sf::Color::Black);
    sf::FloatRect textRect1 = textJouer.getLocalBounds();
    textJouer.setPosition(BUTTON_POS_PLAY);
    //-----------OPTION--------------------
    textOption.setString("Options");
    textOption.setCharacterSize(50);
    textOption.setFillColor(sf::Color::Black);
    sf::FloatRect textRect2 = textOption.getLocalBounds();
    textOption.setPosition(BUTTON_POS_OPT);
    //------------REGLE-------------------
    textRegles.setString("Règles");
    textRegles.setCharacterSize(50);
    textRegles.setFillColor(sf::Color::Black);
    sf::FloatRect textRect3 = textRegles.getLocalBounds();
    textRegles.setPosition(BUTTON_POS_RGL);
    //-----------EXIT------------------
    textExit.setString("Quitter");
    textExit.setCharacterSize(50);
    textExit.setFillColor(sf::Color::Black);
    sf::FloatRect textRect4 = textExit.getLocalBounds();
    textExit.setPosition(BUTTON_POS_EXT);
    //FIN MENU
    //----------------FIN POLICE-------------------------


    buttonPlay.setFillColor(sf::Color::Red);
    buttonOptions.setFillColor(sf::Color::Red);
    buttonRegles.setFillColor(sf::Color::Red);
    buttonExit.setFillColor(sf::Color::Red);




    //--------------------TEST SI LA SOURIS PASSE SUR LE TEXTE------------------------------
    if (isButtonSelect(window, posSouris, BUTTON_POS_PLAY))
    {
        buttonPlay.setFillColor(sf::Color::Black);
        textJouer.setFillColor(sf::Color::White);
    }
    else if (isButtonSelect(window, posSouris, BUTTON_POS_OPT))
    {
        buttonOptions.setFillColor(sf::Color::Black);
        textOption.setFillColor(sf::Color::White);
    }
    else if (isButtonSelect(window, posSouris, BUTTON_POS_RGL))
    {
        buttonRegles.setFillColor(sf::Color::Black);
        textRegles.setFillColor(sf::Color::White);
    }
    else if (isButtonSelect(window, posSouris, BUTTON_POS_EXT))
    {
        buttonExit.setFillColor(sf::Color::Black);
        textExit.setFillColor(sf::Color::White);
    }

    buttonPlay.setPosition(BUTTON_POS_PLAY);
    buttonOptions.setPosition(BUTTON_POS_OPT);
    buttonRegles.setPosition(BUTTON_POS_RGL);
    buttonExit.setPosition(BUTTON_POS_EXT);


    //On dessine tout sur la fenêtre 
    window.draw(buttonPlay);
    window.draw(buttonOptions);
    window.draw(buttonRegles);
    window.draw(buttonExit);
    window.draw(textTitre);
    window.draw(textJouer);
    window.draw(textOption);
    window.draw(textRegles);
    window.draw(textExit);
}

bool isButtonSelect(sf::RenderWindow& window, sf::Vector2i& posSouris, sf::Vector2f posButton)
{
    int res = 0;
    if (posSouris.x >= posButton.x && posSouris.x <= posButton.x + BUTTON_SIZE.x && posSouris.y >= posButton.y && posSouris.y <= posButton.y + BUTTON_SIZE.y)
    {
        res = 1;
    }
    return res;
}
