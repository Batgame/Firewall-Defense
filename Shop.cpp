#include "header/constShop.h"
#include "header/Shop.h"


Shop::Shop() :isActive(0), money(500)
{
	shopDeve = sf::RectangleShape(sf::Vector2f(MENU_SIZE));
	shopNoDeve = sf::RectangleShape(sf::Vector2f(70, 70));
	barre = sf::RectangleShape(sf::Vector2f(WIDTH / 4, 10));

	turret_explain = sf::RectangleShape(sf::Vector2f(EXPLAIN_SIZE));

	sf::FloatRect buttonShopRect = shopNoDeve.getLocalBounds();
	shopNoDeve.setOrigin(buttonShopRect.width / 2.0f, buttonShopRect.height / 2.0f);
}

bool Shop::isOpenMenu()
{
	return isActive;
}


void Shop::beDraw(sf::RenderWindow& window, sf::View view)
{
	sf::Font font;
	sf::Text textShop;
	sf::Text textExitShop;
	sf::Text textTurret1;
	sf::Text textTurret2;
	sf::Text textTurret3;
	sf::Text textTurret4;
	sf::Text textBoutique;

	textShop.setFont(font);
	textExitShop.setFont(font);
	textTurret1.setFont(font);
	textTurret2.setFont(font);
	textTurret3.setFont(font);
	textTurret4.setFont(font);
	textBoutique.setFont(font);

	//----------SET "SHOP" TEXT ----------
	textShop.setString("Shop");
	textShop.setCharacterSize(13);
	textShop.setFillColor(sf::Color::Black);
	sf::FloatRect shopRect = textShop.getLocalBounds();
	textShop.setOrigin(shopRect.width / 2.0f, shopRect.height / 1.25f);
	textShop.setPosition(TEXT_SHOP_POS);

	//-------------SET "BOUTIQUE" TEXT----------------
	textBoutique.setString("Boutique");
	textBoutique.setCharacterSize(22);
	textBoutique.setFillColor(sf::Color::Black);
	sf::FloatRect boutiqueRect = textBoutique.getLocalBounds();
	textBoutique.setOrigin(boutiqueRect.width / 2.0f, boutiqueRect.height / 1.25f);
	textBoutique.setPosition(TEXT_BOUTIQUE_POS);

	//---------SET "LEAVE SHOP" TEXT--------
	textExitShop.setString("Fermer");
	textExitShop.setCharacterSize(13);
	textExitShop.setFillColor(sf::Color::White);
	sf::FloatRect leaveShopRect = textExitShop.getLocalBounds();
	textExitShop.setOrigin(leaveShopRect.width / 2.0f, leaveShopRect.height / 1.25f);
	textExitShop.setPosition(TEXT_LEAVE_SHOP_POS);

	//---------SET "Turret 1" TEXT--------
	textTurret1.setString("AVAST");
	textTurret1.setCharacterSize(12);
	textTurret1.setFillColor(sf::Color::Black);
	sf::FloatRect turretTextRect1 = textTurret1.getLocalBounds();
	textTurret1.setOrigin(turretTextRect1.width / 2.0f, turretTextRect1.height / 1.25f);
	textTurret1.setPosition(TEXT_TURRET_1_POS);

	//---------SET "Turret 2" TEXT--------
	textTurret2.setString("KASPERSKY");
	textTurret2.setCharacterSize(12);
	textTurret2.setFillColor(sf::Color::Black);
	sf::FloatRect turretTextRect2 = textTurret2.getLocalBounds();
	textTurret2.setOrigin(turretTextRect2.width / 2.0f, turretTextRect2.height / 1.25f);
	textTurret2.setPosition(TEXT_TURRET_2_POS);


	//---------SET "Turret 3" TEXT--------
	textTurret3.setString("DEFENDER");
	textTurret3.setCharacterSize(12);
	textTurret3.setFillColor(sf::Color::Black);
	sf::FloatRect turretTextRect3 = textTurret3.getLocalBounds();
	textTurret3.setOrigin(turretTextRect3.width / 2.0f, turretTextRect3.height / 1.25f);
	textTurret3.setPosition(TEXT_TURRET_3_POS);

	//---------SET "Turret 4" TEXT--------
	textTurret4.setString("MC AFFEE");
	textTurret4.setCharacterSize(12);
	textTurret4.setFillColor(sf::Color::Black);
	sf::FloatRect turretTextRect4 = textTurret4.getLocalBounds();
	textTurret4.setOrigin(turretTextRect4.width / 2.0f, turretTextRect4.height / 1.25f);
	textTurret4.setPosition(TEXT_TURRET_4_POS);

	//-----------CHARGEMENT POLICE -------------------
	if (!font.loadFromFile("./addons/font2.ttf")) {

		printf("Impossible de charger la font1.\n");
	}
	//-----------CHARGEMENT DES TEXTURES-------------------
	if (!txtTurret1.loadFromFile("./addons/AvastShop.png"))
	{
		printf("Impossible de charger la Texture 1.\n");
	}
	if (!txtTurret2.loadFromFile("./addons/kasperskyShop.png"))
	{
		printf("Impossible de charger la Texture 2.\n");
	}
	if (!txtTurret3.loadFromFile("./addons/windowDefenderShop.png"))
	{
		printf("Impossible de charger la Texture 3.\n");
	}
	if (!txtTurret4.loadFromFile("./addons/mcAffeeShop.png"))
	{
		printf("Impossible de charger la Texture 4.\n");
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
		shopNoDeve.setFillColor(sf::Color::Black);

		shopDeve.setFillColor(sf::Color::White);
		shopDeve.setPosition(MENU_POS);

		barre.setFillColor(sf::Color::Black);
		barre.setPosition(BARRE_SEPARATION_POS);

		turret_1.setFillColor(sf::Color::Yellow);
		turret_1.setPosition(TURRET_1_POS);
		sprTurret1.setTexture(txtTurret1);
		sprTurret1.setPosition(TURRET_1_POS);
		sprTurret1.setScale(sf::Vector2f(3.f, 3.f));

		turret_2.setFillColor(sf::Color::Yellow);
		turret_2.setPosition(TURRET_2_POS);
		sprTurret2.setTexture(txtTurret2);
		sprTurret2.setPosition(TURRET_2_POS);
		sprTurret2.setScale(sf::Vector2f(3.f, 3.f));

		turret_3.setFillColor(sf::Color::Yellow);
		turret_3.setPosition(TURRET_3_POS);
		sprTurret3.setTexture(txtTurret3);
		sprTurret3.setPosition(TURRET_3_POS);
		sprTurret3.setScale(sf::Vector2f(3.f, 3.f));

		turret_4.setFillColor(sf::Color::Yellow);
		turret_4.setPosition(TURRET_4_POS);
		sprTurret4.setTexture(txtTurret4);
		sprTurret4.setPosition(TURRET_4_POS);
		sprTurret4.setScale(sf::Vector2f(3.f, 3.f));

		window.draw(shopDeve);
		window.draw(shopNoDeve);
		window.draw(barre);

		window.draw(turret_1);
		window.draw(textTurret1);
		window.draw(sprTurret1);

		window.draw(turret_2);
		window.draw(textTurret2);
		window.draw(sprTurret2);

		window.draw(turret_3);
		window.draw(textTurret3);
		window.draw(sprTurret3);

		window.draw(turret_4);
		window.draw(textTurret4);
		window.draw(sprTurret4);

		window.draw(textExitShop);
		window.draw(textBoutique);
	}
}

void Shop::switchActive()
{
	isActive = !isActive;
}


int Shop::turretSelect(sf::RenderWindow& window, sf::Vector2i mousePos, int& turretSel)
{
	//SI ON PASSE LA SOURIS SUR LES TOURS

	//TURRET 1
	if (mousePos.x >= TURRET_1_POS.x && mousePos.x <= TURRET_1_POS.x + TURRET_SIZE.x && mousePos.y >= TURRET_1_POS.y && mousePos.y <= mousePos.y + TURRET_SIZE.y)
	{
		turretSel = AVAST_SHOP;
	}
	//TURRET 2
	if (mousePos.x >= TURRET_2_POS.x && mousePos.x <= TURRET_2_POS.x + TURRET_SIZE.x && mousePos.y >= TURRET_2_POS.y && mousePos.y <= mousePos.y + TURRET_SIZE.y)
	{
		turretSel = KASPERSKY_SHOP;
	}
	//TURRET 3
	if (mousePos.x >= TURRET_3_POS.x && mousePos.x <= TURRET_3_POS.x + TURRET_SIZE.x && mousePos.y >= TURRET_3_POS.y && mousePos.y <= mousePos.y + TURRET_SIZE.y)
	{
		turretSel = DEFENDER_SHOP;
	}
	//TURRET 4
	if (mousePos.x >= TURRET_4_POS.x && mousePos.x <= TURRET_4_POS.x + TURRET_SIZE.x && mousePos.y >= TURRET_4_POS.y && mousePos.y <= mousePos.y + TURRET_SIZE.y)
	{
		turretSel = MCAFEE_SHOP;
	}
	return turretSel;
	if (mousePos.x >= BUTTON_POS.x && mousePos.x <= BUTTON_POS.x + BUTTON_SIZE.x && mousePos.y >= BUTTON_POS.y && mousePos.y <= mousePos.y + BUTTON_SIZE.y)
	{
		turretSel = EXPLAIN_SHOP;
	}
	return turretSel;
}

void Shop::turretExplain(sf::RenderWindow& window, int turretSelect)
{
	sf::Font font;

	sf::Text textExplainEmpty;
	sf::Text textExplainTurret1;
	sf::Text textExplainTurret2;
	sf::Text textExplainTurret3;
	sf::Text textExplainTurret4;

	sf::CircleShape cercle(10.f);

	textExplainEmpty.setFont(font);
	textExplainTurret1.setFont(font);
	textExplainTurret2.setFont(font);
	textExplainTurret3.setFont(font);
	textExplainTurret4.setFont(font);

	if (!font.loadFromFile("./addons/font2.ttf"))
	{
		printf("Impossible de charger la font1.\n");
	}

	turret_explain.setPosition(EXPLAIN_POS);

	if (turretSelect == AVAST_SHOP)
	{
		// --------------EXPLICATION TOURELLE 1--------------------
		textExplainTurret1.setString("Avast : Défense basique. \nCadence rapide mais \nfaible dégats");
		textExplainTurret1.setCharacterSize(14);
		textExplainTurret1.setFillColor(sf::Color::Black);
		//sf::FloatRect explainRect1 = textExplainTurret1.getLocalBounds();
		//textExplainTurret1.setOrigin(explainRect1.width / 2.0f, explainRect1.height / 1.25f);

		textExplainTurret1.setPosition(EXPLAIN_TEXT_POS);

		window.draw(textExplainTurret1);
		window.draw(cercle);
	}
	else if (turretSelect == KASPERSKY_SHOP)
	{
		// --------------EXPLICATION TOURELLE 2--------------------
		textExplainTurret2.setString("Kaspersky : Défense lourde. \nTir de puissants mortiers \nà faible cadence.");
		textExplainTurret2.setCharacterSize(14);
		textExplainTurret2.setFillColor(sf::Color::Black);
		//sf::FloatRect explainRect2 = textExplainTurret2.getLocalBounds();
		//textExplainTurret2.setOrigin(explainRect2.width / 2.0f, explainRect2.height / 1.25f);
		textExplainTurret2.setPosition(EXPLAIN_TEXT_POS);
		window.draw(textExplainTurret2);
	}
	else if (turretSelect == DEFENDER_SHOP)
	{
		// --------------EXPLICATION TOURELLE 3--------------------
		textExplainTurret3.setString("Defender : Défense legère.\nFais des dégats sur une \ncourte portée autour de lui");
		textExplainTurret3.setCharacterSize(14);
		textExplainTurret3.setFillColor(sf::Color::Black);
		//sf::FloatRect explainRect3 = textExplainTurret3.getLocalBounds();
		//textExplainTurret3.setOrigin(explainRect3.width / 2.0f, explainRect3.height / 1.25f);
		textExplainTurret3.setPosition(EXPLAIN_TEXT_POS);
		window.draw(textExplainTurret3);
	}
	else if (turretSelect == MCAFEE_SHOP)
	{
		// --------------EXPLICATION TOURELLE 4--------------------
		textExplainTurret4.setString("Mc Afee : Défense lourde. \nInflige des dégats à tous les \nvirus présent sur le chemin");
		textExplainTurret4.setCharacterSize(14);
		textExplainTurret4.setFillColor(sf::Color::Black);
		//sf::FloatRect explainRect4 = textExplainTurret4.getLocalBounds();
		//textExplainTurret4.setOrigin(explainRect4.width / 2.0f, explainRect4.height / 1.25f);
		textExplainTurret4.setPosition(EXPLAIN_TEXT_POS);
		window.draw(textExplainTurret4);
	}
	else if (turretSelect == EXPLAIN_SHOP)
	{
		//-------------EXPLICATION BOUTIQUE--------------
		textExplainEmpty.setString("Cliquez sur une tourelle \npour voir leurs \ncaractéristiques");
		textExplainEmpty.setCharacterSize(14);
		textExplainEmpty.setFillColor(sf::Color::Black);
		//sf::FloatRect explainRectEmpty = textExplainEmpty.getLocalBounds();
		//textExplainEmpty.setOrigin(explainRectEmpty.width / 2.0f, explainRectEmpty.height / 1.25f);
		textExplainEmpty.setPosition(EXPLAIN_TEXT_POS);
		window.draw(textExplainEmpty);
	}
}
