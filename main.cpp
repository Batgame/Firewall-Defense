#include <SFML/Graphics.hpp>
#include <iostream>
#include "header/constShop.h"
#include "header/Shop.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Firewall-Defense");
	sf::View view(sf::Vector2f(450, 450), sf::Vector2f(WIDTH, HEIGHT));
	
	sf::Event event;
	sf::Vector2i mousePos;
	sf::Vector2f posMenu;
	sf::Clock clock;
	sf::Time dt;

	Shop magasin;
	bool flag = false;
	bool isActive = 0;
	mousePos = sf::Mouse::getPosition(window);

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
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (event.mouseButton.x >= (BUTTON_POS.x - (0.5 * BUTTON_SIZE.x)) && event.mouseButton.x <= BUTTON_POS.x + (0.5 * BUTTON_SIZE.x) && event.mouseButton.y >= (BUTTON_POS.y - 0.5 * BUTTON_SIZE.y) && event.mouseButton.y <= BUTTON_POS.y + 0.5 * BUTTON_SIZE.y) //sont dedans
					{
						if (flag)
						{
							isActive = !isActive;
							flag = false;
						}
						else
						{
							isActive = true;
							flag = true;
						}
					}
				}
			}
		}

		dt = clock.restart();
		window.clear();

		//isActive = magasin.isOpenMenu(window, mousePos);
		
		//On simule la ou le jeu sera
		sf::RectangleShape jeu(sf::Vector2f(WIDTH, HEIGHT)); 
		jeu.setFillColor(sf::Color::Black);
		jeu.setPosition(0, 0);
		window.draw(jeu);

		if(flag == true )
		{
			isActive = true;
			magasin.beDraw(window, mousePos, isActive, dt);
		}
		else {
			isActive = false;
			magasin.beDraw(window, mousePos, isActive, dt);
		}
		window.display();
	}
}
