#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "menu.h"
#include "const.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Button");
    sf::View view(sf::Vector2f(450, 450), sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
      
    //variables
    sf::Vector2i posSouris;
    sf::Event event;
    int mouseX = posSouris.x;
    int mouseY = posSouris.y;

    

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
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
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            //Event souris
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    //
                }
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    //
                }
            }
        }
        posSouris = sf::Mouse::getPosition(window);
        window.clear();

        beDraw(window, posSouris);

        window.display();
    }
}



void beDraw(sf::RenderWindow& window, sf::Vector2i& posSouris)
{
    sf::RectangleShape buttonPlay(sf::Vector2f(LARGEUR_RECT, HAUTEUR_RECT));
    sf::RectangleShape buttonOptions(sf::Vector2f(LARGEUR_RECT, HAUTEUR_RECT));
    sf::RectangleShape buttonRegles(sf::Vector2f(LARGEUR_RECT, HAUTEUR_RECT));
    sf::RectangleShape buttonExit(sf::Vector2f(LARGEUR_RECT, HAUTEUR_RECT));

    buttonPlay.setFillColor(sf::Color::Red);
    buttonOptions.setFillColor(sf::Color::Blue);
    buttonRegles.setFillColor(sf::Color::Green);
    buttonExit.setFillColor(sf::Color::Yellow);

    buttonPlay.setPosition(BUTTON_POS_PLAY);
    buttonOptions.setPosition(BUTTON_POS_OPT);
    buttonRegles.setPosition(BUTTON_POS_RGL);
    buttonExit.setPosition(BUTTON_POS_EXT);

    //Changement de couleur pour les boutons
    printf("pos en x : %i ------ pos en y : %i \n", posSouris.x, posSouris.y);

    if (isButtonSelect(window, posSouris, BUTTON_POS_PLAY))
    {
        buttonPlay.setFillColor(sf::Color::White);
    }
    else if (isButtonSelect(window, posSouris, BUTTON_POS_OPT))
    {
        buttonOptions.setFillColor(sf::Color::White);
    }
    else if (isButtonSelect(window, posSouris, BUTTON_POS_RGL))
    {
        buttonRegles.setFillColor(sf::Color::White);
    }
    else if (isButtonSelect(window, posSouris, BUTTON_POS_EXT))
    {
        buttonExit.setFillColor(sf::Color::White);
    }
    
    window.draw(buttonPlay);
    window.draw(buttonOptions);
    window.draw(buttonRegles);
    window.draw(buttonExit);
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
