#include <SFML/Graphics.hpp>
#include <iostream>
#include "constShop.h"
#include "Shop.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Firewall-Defense");
	sf::View view(sf::Vector2f(450, 450), sf::Vector2f(WIDTH, HEIGHT));
	
	sf::Event event;
	sf::Vector2i mousePos;
	sf::Vector2f posMenu;

	Shop magasin;

	bool isActive;

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

			if (event.type == sf::Event::MouseButtonPressed)
			{

			}
		}


		window.clear();

		isActive = magasin.isOpenMenu(window, mousePos);
		

		//On simule la ou le jeu sera
		sf::RectangleShape jeu(sf::Vector2f(WIDTH, HEIGHT)); 
		jeu.setFillColor(sf::Color::Black);
		jeu.setPosition(0, 0);
		window.draw(jeu);
		

		magasin.beDraw(window, mousePos, isActive);

		window.display();
	}
}
