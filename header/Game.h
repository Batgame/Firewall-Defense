#pragma once
#include "Projectile.h"
#include "Trojan.h"
#include "Turret.h"
#include "Mortar.h"
#include "Spritesheet.h"
#include "USBKiller.h"

#define DELAY_SPAWN 0.3
#define DELAY_WAVE 10

#define AVAST_PRICE 100
#define KASPERSKY_PRICE 500
#define DEFENDER_PRICE 300
#define MCAFEE_PRICE 1000

#define TROJAN_VALUE 100
#define USBKILLER_VALUE 50

#define TROJAN_DAMAGE 20
#define USBKILLER_DAMAGE 5



class Game
{
	int selectedTurret;
	float delaySpawn;
	int map;

	int sizeX;
	int sizeY;
	std::vector<int> bg;

	std::vector<Road> roads;
	std::vector<Projectile> projectiles;
	std::vector<Mortar> mortars;
	std::vector<Trojan> trojans;
	std::vector<USBKiller> usbKillers;
	std::vector<Turret> turrets;
	float delayWave;
	int trojanCount;
	int usbKillerCount;
	int money;
	int level;
	int hp;

	void levelUp();

public :
	Spritesheet sprsAvast;
	Spritesheet sprsKaspersky;
	Spritesheet sprsUSBKillers;
	Spritesheet sprsTrojan;

	sf::Texture textureRoadVertical;
	sf::Sprite sprRoadVertical;

	sf::Texture textureRoadHorizontal;
	sf::Sprite sprRoadHorizontal;

	sf::Texture textureRoadAngle;
	sf::Sprite sprRoadAngle;

	sf::Texture textureRoadInter;
	sf::Sprite sprRoadInter;

	sf::Texture textureMoney;
	sf::Sprite sprMoney;

	//--------------------BackGround---------------------

	sf::Texture textureBg0;
	sf::Sprite sprBg0;

	sf::Texture textureBg1;
	sf::Sprite sprBg1;

	sf::Texture textureBg2;
	sf::Sprite sprBg2;

	sf::Texture textureBg3;
	sf::Sprite sprBg3;

	sf::Texture textureHp;
	sf::Sprite sprHp;

	//Constructeur de la classe Game
	Game(int map_ = 1);
	//Refresh le jeux dans le temps
	void refresh(sf::Time& dt);
	//Dessine le jeux
	void beDraw(sf::RenderWindow& rWindow,sf::View const& view);
	//Refresh les tourelles	
	void refreshTurrets(sf::Time const& dt);
	//Setup la tourelle séléctionné via le shop
	void setSelectedTurret(int const& turret);
	//Achete une tourelles et la pose
	void buyTurret(int& mouseX, int& mouseY, sf::RenderWindow& rWindow, sf::View view);
	//Vend une tourelle
	void sellTurret(int& mouseX, int& mouseY, sf::RenderWindow& rWindow, sf::View view);
	//Retourne vrai si je le jeux est perdu
	bool isLoose();
	//Retourne la vague actuelle
	int getLevel();
	//Recommence le jeu en cas de défaite
	void restart();

};