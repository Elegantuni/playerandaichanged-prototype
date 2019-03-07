#pragma once

struct aicharacter
{
	int y;
	int x;
	int hitpoints;
	int magicpoints;
	int defensepoints;
	char* weapon;
	char* shield;
	char* charactersign;
	int prevy;
	int prevx;
	int magicattack;
	int count;
	int replayer;
	int playerturn;
	struct weaponsenemies weapontype;
	struct weaponsdamageenemies weaponsdamage1;
	int randomitem;
	struct shieldsenemies shieldstype;
	struct shieldsdamageenemies shieldsdamage1;
	int shieldsrandomitem;
	struct charactertemp character1;
	struct magicenemies magic1;
	struct armorenemies armor1;
};
