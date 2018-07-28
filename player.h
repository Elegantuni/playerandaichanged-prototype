#pragma once

struct player
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
	struct weapons weapontype;
	struct weaponsdamage weaponsdamage1;
	int randomitem;
	struct shields shieldstype;
	struct shieldsdamage shieldsdamage1;
	int shieldsrandomitem;
	struct charactertemp character1;
	struct magic magic1;
	struct armor armor1;
};
