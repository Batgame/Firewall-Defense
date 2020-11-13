#pragma once
#include "Projectile"

enum e_id_Turret
{
	AVAST, //Tourelle Rapid mais peu de dégat
	AVIRA, 
	WINDOW_DEFENDER,
	KASPERSKY
};

#define CD_AVAST 0.3
#define DMG_AVAST 1


class Turret
{
	float coolDown;
	int damage;
	int id;

public : 

	Turret(int id_ = 0);
	Projectile create();


};

