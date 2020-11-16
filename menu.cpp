#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "const.h"
#include "menu.h"
#include "TextureManager.h"

extern sf::Font font;

/*
------------------------------------TO DO-----------------------------------------------------
- faire un truc plus disign
- centrer le texte sur bouton (il y a peut etre une fonction qui permet de le faire mais je l'ai pas trouv�(c'est mathis qui me l'a dis))
- Faire la continuit� du menu lorsque l'on clique sur les boutons
*/

enum e_id_gameMode {
    MENU,
    REGLES,
    OPTIONS,
    INGAME,
    LOADING,    //Risque de ne pas �tre utilis� (Pas de chargement n�cessaire)
};

//---------------------------------FONCTIONS---------------------------
/*
La fonction dessine : 
    - Les Rectangles
    - Les textes
    - Les changements de couleurs des boutons lorsque la souris passes dessus
    - Les changements de couleurs de texte lorsque la souris passe dessus ( /!\ TO DO /!\ )
*/

void drawMenu(sf::RenderWindow& window, sf::Vector2i& posSouris, sf::View view)
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

void drowRegles(sf::RenderWindow& window, sf::Vector2i& posSouris, sf::View view)
{

    //Cr�ation button Exit
    sf::RectangleShape buttonRetour(sf::Vector2f(LARGEUR_RECT, HAUTEUR_RECT));
    sf::FloatRect buttonRetourRect = buttonRetour.getLocalBounds();
    buttonRetour.setOrigin(buttonRetourRect.width / 2.0f, buttonRetourRect.height / 2.0f);

    sf::Text textTitre;
    sf::Text textRetour;
    sf::Text textRegles;

    //INITIALISATION
    textTitre.setFont(font);
    textRetour.setFont(font);
    textRegles.setFont(font);

    //--------------------POLICE-------------------------

    //DEBUT TITRE
    textTitre.setString("Firewall-Defense");
    textTitre.setCharacterSize(100);
    textTitre.setFillColor(sf::Color::White);
    sf::FloatRect titreRect = textTitre.getLocalBounds();
    textTitre.setOrigin(titreRect.width / 2.0f, titreRect.height / 2.0f);
    textTitre.setPosition(TEXT_TITRE_POS);
    //FIN TITRE

    //DEBUT MENU
    //-----------Regles----------------
    textRegles.setString("Firewall d�fense est un jeu bas� sur le concept de Tower Defense.\n\nVotre but est de d�fendre l'entr�e de virus et les emp�cher d'arriver � la \nfin du chemin. Pour cela, vous pouvez construire des tours aux capacit�s \ndiff�rentes pour d�fendre votre chemin.Attention, si vous laissez passer \ntrop de virus, ils d�truiront votre syst�me d'exploitation.\n\nBonne chance !");
    textRegles.setCharacterSize(25);
    //textRegles.setFillColor(sf::Color(249, 129, 58));
    textRegles.setFillColor(sf::Color::White);
    //sf::FloatRect reglesRect = textRegles.getLocalBounds();
    //textRegles.setOrigin(reglesRect.width / 2.0f, reglesRect.height / 2.0f);
    textRegles.setPosition(TEXT_REGLES_POS);

    //-----------RETOUR------------------
    textRetour.setString("Retour");
    textRetour.setCharacterSize(TEXT_SIZE);
    textRetour.setFillColor(sf::Color::White);
    sf::FloatRect retourRect = textRetour.getLocalBounds();
    textRetour.setOrigin(retourRect.width / 2.0f, retourRect.height / 1.25f);
    textRetour.setPosition(BUTTON_POS_RET);
    //FIN MENU
    //----------------FIN POLICE-------------------------

    buttonRetour.setFillColor(sf::Color(11, 46, 150));

    //--------------------TEST SI LA SOURIS PASSE SUR LE TEXTE------------------------------

    if (isButtonSelect(window, posSouris, BUTTON_POS_RET))
    {
        buttonRetour.setFillColor(sf::Color::Black);
        textRetour.setFillColor(sf::Color::White);
    }

    buttonRetour.setPosition(BUTTON_POS_RET);


    //On dessine tout sur la fen�tre 
    window.draw(buttonRetour);
    window.draw(textTitre);
    window.draw(textRetour);
    window.draw(textRegles);
}

bool isButtonSelect(sf::RenderWindow& window, sf::Vector2i& posSouris, sf::Vector2f posButton)
{
    int res = 0;
    if (posSouris.x >= (posButton.x - (0.3 * BUTTON_SIZE.x)) && posSouris.x <= posButton.x + (0.3 * BUTTON_SIZE.x) && posSouris.y >= (posButton.y - 0.5 * BUTTON_SIZE.y) && posSouris.y <= posButton.y + 0.5 * BUTTON_SIZE.y)
    {
        res = 1;
    }
    return res;
}
