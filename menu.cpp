#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "header/const.h"
#include "header/menu.h"



/*
------------------------------------TO DO-----------------------------------------------------
- faire un truc plus disign
- centrer le texte sur bouton (il y a peut etre une fonction qui permet de le faire mais je l'ai pas trouv�(c'est mathis qui me l'a dis))
- Faire la continuit� du menu lorsque l'on clique sur les boutons
*/



int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Firewall-Defense");
    sf::View view(sf::Vector2f(450, 450), sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

    sf::Texture img_background;
    sf::Vector2i posSouris;
    sf::Event event;

    //-----------------IMAGE BACJGROUND----------------------------
	if (!img_background.loadFromFile("./addons/mother-board.png"))
	{
		printf("Pb de chargement de l'image.\n");
	}
	sf::Sprite background;
	background.setScale(0.42f, 0.25f);
	background.setOrigin(0, 0);
	background.setTexture(img_background);

    //-------------FIN IMAGE BACKGROUND----------------------------
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
            //--------------------------Resise de la fen�tre----------------------------------
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
                        printf("Voici les r�gles du jeu !\n");
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
    //Cr�ation button Play
    sf::RectangleShape buttonPlay(sf::Vector2f(LARGEUR_RECT, HAUTEUR_RECT));
    sf::FloatRect buttonPlayRect = buttonPlay.getLocalBounds();
    buttonPlay.setOrigin(buttonPlayRect.width / 2.0f, buttonPlayRect.height / 2.0f);

    //Cr�ation button Options
    sf::RectangleShape buttonOptions(sf::Vector2f(LARGEUR_RECT, HAUTEUR_RECT));
    sf::FloatRect buttonOptionsRect = buttonOptions.getLocalBounds();
    buttonOptions.setOrigin(buttonOptionsRect.width / 2.0f, buttonOptionsRect.height / 2.0f);

    //Cr�ation button R�gle
    sf::RectangleShape buttonRegles(sf::Vector2f(LARGEUR_RECT, HAUTEUR_RECT));
    sf::FloatRect buttonReglesRect = buttonRegles.getLocalBounds();
    buttonRegles.setOrigin(buttonReglesRect.width / 2.0f, buttonReglesRect.height / 2.0f);

    //Cr�ation button Exit
    sf::RectangleShape buttonExit(sf::Vector2f(LARGEUR_RECT, HAUTEUR_RECT));
    sf::FloatRect buttonExitRect = buttonExit.getLocalBounds();
    buttonExit.setOrigin(buttonExitRect.width / 2.0f, buttonExitRect.height / 2.0f);

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
    textTitre.setFillColor(sf::Color::White);
    sf::FloatRect titreRect = textTitre.getLocalBounds();
    textTitre.setOrigin(titreRect.width / 2.0f, titreRect.height / 2.0f);
    textTitre.setPosition(TEXT_TITRE_POS);
    //FIN TITRE

    //DEBUT MENU
    //-----------JOUER----------------
    textJouer.setString("Jouer");
    textJouer.setCharacterSize(TEXT_SIZE);
    textJouer.setFillColor(sf::Color::White);
    sf::FloatRect jouerRect = textJouer.getLocalBounds();
    textJouer.setOrigin(jouerRect.width / 2.0f, jouerRect.height / 1.25f);
    textJouer.setPosition(BUTTON_POS_PLAY);
    

    //-----------OPTION--------------------
    textOption.setString("Options");
    textOption.setCharacterSize(TEXT_SIZE);
    textOption.setFillColor(sf::Color::White);
    sf::FloatRect optionsRect = textOption.getLocalBounds();
    textOption.setOrigin(optionsRect.width / 2.0f, optionsRect.height / 1.25f);
    textOption.setPosition(BUTTON_POS_OPT);
    //------------REGLE-------------------
    textRegles.setString("R�gles");
    textRegles.setCharacterSize(TEXT_SIZE);
    textRegles.setFillColor(sf::Color::White);
    sf::FloatRect reglesRect = textRegles.getLocalBounds();
    textRegles.setOrigin(reglesRect.width / 2.0f, reglesRect.height / 1.25f);
    textRegles.setPosition(BUTTON_POS_RGL);
    //-----------EXIT------------------
    textExit.setString("Quitter");
    textExit.setCharacterSize(TEXT_SIZE);
    textExit.setFillColor(sf::Color::White);
    sf::FloatRect exitRect = textRegles.getLocalBounds();
    textExit.setOrigin(exitRect.width / 2.0f, exitRect.height / 1.25f);
    textExit.setPosition(BUTTON_POS_EXT);
    //FIN MENU
    //----------------FIN POLICE-------------------------


    buttonPlay.setFillColor(sf::Color(11, 46, 150));
    buttonOptions.setFillColor(sf::Color(11, 46, 150));
    buttonRegles.setFillColor(sf::Color(11, 46, 150));
    buttonExit.setFillColor(sf::Color(11, 46, 150));




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


    //On dessine tout sur la fen�tre 
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
    if (posSouris.x >= (posButton.x - (0.5 * BUTTON_SIZE.x)) && posSouris.x <= posButton.x + (0.5 * BUTTON_SIZE.x) && posSouris.y >= (posButton.y - 0.5 * BUTTON_SIZE.y) && posSouris.y <= posButton.y + 0.5 * BUTTON_SIZE.y)
    {
        res = 1;
    }
    return res;
}
