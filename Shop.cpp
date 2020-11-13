#include "Shop.h"
#include "constShop.h"

void Shop::buyTurret(int idAachat)
{
	switch (idAchat)
	{
	case 1: //Si il achete la premiere tour

		//drag and drop la tourel  ?
		money -= PRIX_TOUR_1;
		break;
	case 2: //Si il achete la deuxième tour

		//drag and drop la tourel  ?
		money -= PRIX_TOUR_2;
		break;
	case 3: //Si il achete la troisième tour

		//drag and drop la tourel  ?

		money -= PRIX_TOUR_3;
		break;
	}
}


Shop::Shop() :isActive(0), money(500)
{

}

bool Shop::isOpenMenu(sf::RenderWindow& window, sf::Vector2i mousePos)
{
	mousePos = sf::Mouse::getPosition(window);
	if (mousePos.x >= BUTTON_POS.x && mousePos.x <= BUTTON_POS.x + BUTTON_SIZE.x && BUTTON_POS.y >= BUTTON_POS.y && mousePos.y <= BUTTON_POS.y + BUTTON_SIZE.y)
	{
		isActive = 1;
	}
	else if(!(mousePos.x >= MENU_POS.x && mousePos.x <= MENU_POS.x + MENU_SIZE.x && MENU_POS.y >= MENU_POS.y && mousePos.y <= MENU_POS.y + MENU_SIZE.y))
	{
		isActive = 0;
	}


	return isActive;
}


void Shop::beDraw(sf::RenderWindow& window, sf::Vector2i mousePos, bool isActive)
{
	
	if (!isActive)
	{
		sf::RectangleShape shopNoDev(sf::Vector2f(50, 50));
		shopNoDev.setFillColor(sf::Color::White); 
		shopNoDev.setPosition(WIDTH - 50, 0);
		window.draw(shopNoDev);
	}
	else
	{
		bool movement = 0;
		sf::RectangleShape shopDeve(sf::Vector2f(MENU_SIZE));
		shopDeve.setFillColor(sf::Color::Blue);


		do
		{
			shopDeve.move(-2, 0);
			if (shopDeve.getPosition().x < MENU_POS.x)
			{
				shopDeve.setPosition(MENU_POS);
				movement = 0;
			}
			else
			{
				movement = 1;
			}
			shopDeve.getPosition();
			shopDeve.setPosition(MENU_POS);
		} while (movement);


		window.draw(shopDeve);
	}
}
