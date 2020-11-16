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

#define TROJAN_VALUE 25
#define USBKILLER_VALUE 10


class Game
{
	Spritesheet sprsAvast;
	Spritesheet sprsKaspersky;
	Spritesheet sprsUSBKillers;
	Spritesheet sprsTrojan;
	sf::Texture bg;
	sf::Sprite sprBg;

	int selectedTurret;
	float delaySpawn;
	int map;
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

public :

	Game(int map_ = 1);
	void refresh(sf::Time& dt);
	void beDraw(sf::RenderWindow& rWindow,sf::View const& view);
	void refreshTurrets(sf::Time const& dt);
	void setSelectedTurret(int const& turret);
	void buyTurret(int& mouseX, int& mouseY, sf::RenderWindow& rWindow, sf::View view);
	void sellTurret(int& mouseX, int& mouseY, sf::RenderWindow& rWindow, sf::View view);
	void levelUp();
};