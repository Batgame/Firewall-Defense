#include "header/constShop.h"
#include "header/Shop.h"



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
	shopDeve = sf::RectangleShape(sf::Vector2f(MENU_SIZE));
	shopNoDeve = sf::RectangleShape(sf::Vector2f(50, 50));
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

void Shop::beDraw(sf::RenderWindow& window, sf::Vector2i mousePos, bool isActive, sf::Time dt)
{

	if (!isActive)
	{
		shopDeve.setPosition(WIDTH, 0);
		shopNoDeve.setFillColor(sf::Color::White); 
		shopNoDeve.setPosition(WIDTH - 50, 0);
		window.draw(shopNoDeve);

	}
	else
	{
		shopDeve.setFillColor(sf::Color::Blue);

		shopDeve.move((-dt.asSeconds())*100, 0);
		if (shopDeve.getPosition().x < MENU_POS.x)
		{
			shopDeve.setPosition(MENU_POS);
		}
		shopDeve.getPosition();
		shopDeve.setPosition(MENU_POS);

		window.draw(shopDeve);
	}
}
