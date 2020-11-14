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
	case 2: //Si il achete la deuxi�me tour

		//drag and drop la tourel  ?
		money -= PRIX_TOUR_2;
		break;
	case 3: //Si il achete la troisi�me tour

		//drag and drop la tourel  ?

		money -= PRIX_TOUR_3;
		break;
	}
}


Shop::Shop() :isActive(0), money(500)
{	
	shopDeve = sf::RectangleShape(sf::Vector2f(MENU_SIZE));
	shopNoDeve = sf::RectangleShape(sf::Vector2f(70, 70));
	sf::FloatRect buttonShopRect = shopNoDeve.getLocalBounds();
	shopNoDeve.setOrigin(buttonShopRect.width / 2.0f, buttonShopRect.height / 2.0f);
	
}

bool Shop::isOpenMenu(sf::RenderWindow& window, sf::Vector2i mousePos)
{
	mousePos = sf::Mouse::getPosition(window);
	//if (mousePos.x >= (BUTTON_POS.x - (0.5 * BUTTON_SIZE.x)) && mousePos.x <= BUTTON_POS.x + (0.5 * BUTTON_SIZE.x) && mousePos.y >= (BUTTON_POS.y - 0.5 * BUTTON_SIZE.y) && mousePos.y <= BUTTON_POS.y + 0.5 * BUTTON_SIZE.y)
	//{
		//isActive = 1;
	//}
	//else 
	//{
		//isActive = 0;
	//}

	sf::Event event;

	


	return isActive;
}

void Shop::beDraw(sf::RenderWindow& window, sf::Vector2i mousePos, bool isActive, sf::Time dt)
{
	sf::Font font;
	sf::Text textShop;
	sf::Text textExitShop;

	textShop.setFont(font);
	textExitShop.setFont(font);

	//----------SET "SHOP" TEXT ----------
	textShop.setString("Shop");
	textShop.setCharacterSize(13);
	textShop.setFillColor(sf::Color::Black);
	sf::FloatRect shopRect = textShop.getLocalBounds();
	textShop.setOrigin(shopRect.width / 2.0f, shopRect.height / 1.25f);
	textShop.setPosition(TEXT_SHOP_POS);

	//---------SET "LEAVE SHOP" TEXT--------
	textExitShop.setString("Fermer");
	textExitShop.setCharacterSize(13);
	textExitShop.setFillColor(sf::Color::Black);
	sf::FloatRect leaveShopRect = textExitShop.getLocalBounds();
	textExitShop.setOrigin(leaveShopRect.width / 2.0f, leaveShopRect.height / 1.25f);
	textExitShop.setPosition(TEXT_LEAVE_SHOP_POS);

	if (!font.loadFromFile("./addons/font2.ttf")) {

		printf("Impossible de charger la font1.\n");
	}
	if (!isActive)
	{
		shopDeve.setPosition(WIDTH, 0);
		shopNoDeve.setFillColor(sf::Color::White); 
		shopNoDeve.setPosition(BUTTON_POS);

		window.draw(shopNoDeve);
		window.draw(textShop);

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
		window.draw(shopNoDeve);
		window.draw(textExitShop);
	}
}
